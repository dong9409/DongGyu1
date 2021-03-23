from flask import *
import pyrebase
import time
from werkzeug import secure_filename

#플라스크 프로젝트 시작후 앱키 설정
app = Flask(__name__)
app.config["SECRET_KEY"] = "ABCD"

#파이어베이스 연결을 위한 key.json 설정
f = open("key.json")
key = json.load(f)

#파이어베이스 연결
firebase = pyrebase.initialize_app(key)
storage = firebase.storage()
db = firebase.database()


#시작전에 데이터들을 등록함
def insertData():
    global db
    global storage

    db = firebase.database()


    db.child("user").child("0").update({"user_id": "v6752100"})
    db.child("user").child("0").update({"user_name": "Jinje Kim0"})
    db.child("user").child("0").update({"password": int("012345")})

    db.child("user").child("1").update({"user_id": "v6752101"})
    db.child("user").child("1").update({"user_name": "Jinje Kim1"})
    db.child("user").child("1").update({"password": int("123456")})

    db.child("user").child("2").update({"user_id": "v6752102"})
    db.child("user").child("2").update({"user_name": "Jinje Kim2"})
    db.child("user").child("2").update({"password": int("234567")})

    db.child("user").child("3").update({"user_id": "v6752103"})
    db.child("user").child("3").update({"user_name": "Jinje Kim3"})
    db.child("user").child("3").update({"password": int("345678")})

    db.child("user").child("4").update({"user_id": "v6752104"})
    db.child("user").child("4").update({"user_name": "Jinje Kim4"})
    db.child("user").child("4").update({"password": int("456789")})

    db.child("user").child("5").update({"user_id": "v6752105"})
    db.child("user").child("5").update({"user_name": "Jinje Kim5"})
    db.child("user").child("5").update({"password": int("567890")})

    db.child("user").child("6").update({"user_id": "v6752106"})
    db.child("user").child("6").update({"user_name": "Jinje Kim6"})
    db.child("user").child("6").update({"password": int("678901")})

    db.child("user").child("7").update({"user_id": "v6752107"})
    db.child("user").child("7").update({"user_name": "Jinje Kim7"})
    db.child("user").child("7").update({"password": int("789012")})

    db.child("user").child("8").update({"user_id": "v6752108"})
    db.child("user").child("8").update({"user_name": "Jinje Kim8"})
    db.child("user").child("8").update({"password": int("890123")})

    db.child("user").child("9").update({"user_id": "v6752109"})
    db.child("user").child("9").update({"user_name": "Jinje Kim9"})
    db.child("user").child("9").update({"password": int("901234")})
    db.child("user").update({"count": 10})

    for i in range(10):
        db.child("message").push({"subject": f"title{i}",
                                  "message": f"message{i}",
                                  "time": time.strftime('%y-%m-%d'),
                                  "imgUrl": storage.child(str(i) + ".jpg").get_url(None),
                                  "writer": f"writer{i}"})

# "localhost:5000/" 주소에 해당하는 컨트롤러
@app.route('/')
def home():
    return redirect(url_for('login')) #여기로 접속하면 login이라는 html을 리턴함


@app.route('/register', methods = ['GET', 'POST']) #"http://localhost:5000/register" 주소에 해당하는 컨트롤러
def register():
    if request.method == 'POST': #POST형태로 이 주소로 접속하면
        global db
        global storage

        #html에서 입력한 사용자 정보를 받아와서
        firstName = request.form["firstName"]
        lastName = request.form["lastName"]
        fullName = firstName + " " + lastName


        id = request.form["id"]
        file = request.files['file']
        pw = request.form["pw"]
        pwAgain = request.form["pwAgain"]

        #아이디 중복 검사및 비밀번호 검사를 통과후
        if len(db.child("user").order_by_child("user_id").equal_to(id).get().val()) != 0:
            flash("The ID already exits")
            return redirect(url_for('register'))
        elif len(db.child("user").order_by_child("user_name").equal_to(fullName).get().val()) != 0:
            flash("The username already exits")
            return redirect(url_for('register'))
        elif pw != pwAgain:
            flash("비밀번호가 서로 일치하지 않습니다")
            return redirect(url_for('register'))
        elif file.filename == '':
            flash("사진을 첨부해주세요")
            return redirect(url_for('register'))
        else: #여기서 회원정보를 등록함
            currentUserCount = db.child("user").child("count").get().val()
            userNumber = currentUserCount
            db.child("user").child(userNumber).update({"user_id": id}) #파이어베이스에 이러한 json 형태로 등록
            db.child("user").child(userNumber).update({"user_name": fullName})
            db.child("user").child(userNumber).update({"password": int(pw)})
            db.child("user").update({"count": currentUserCount+1})

            filename = secure_filename(file.filename)
            file.save("static/images/" + filename)
            uploadUrl = str(currentUserCount) + ".jpg"
            path_local = f"static/images/{filename}"
            storage.child(uploadUrl).put(path_local)

            return redirect(url_for('login')) #등록에 성공하면 login.html을 리턴하고

    return render_template('register.html') #등록에 실패하면 register.html을 리턴함

@app.route('/login', methods = ['GET', 'POST']) #"http://localhost:5000/login" 주소에 해당하는 컨트롤러
def login():
    if request.method == 'POST': #POST형식으로 이 주소에 접근하면
        global db
        global storage

        #html에서 id와 pw정보를 받아와서
        id = request.form["id"]
        pw = int(request.form["pw"])

        #해당하는 사용자 정보를 파이어베이스에서 읽어옴
        userObject = db.child("user").order_by_child("user_id").equal_to(id).get().val()

        if len(userObject) != 0: #만약에 파이어베이스에서 정보가 왔다면 == 길이가 0이 아니라면 == 사용자가 등록되어 있다면
            user_pw = userObject.popitem(last=True)[1]["password"] #사용자 비밀번호르 받아와서
            if user_pw == pw: #html에서 입력된 비밀번호라 같은지 확인하고
                session["currentUser"] = id #같으면 세션에다가 id를 등록해줘서 현재 사용자를 알려줌
                return redirect(url_for("forum")) #로그인 성공했으니 forum 페이지로감
            else:
                flash("incorrect password") #비밀번호 틀렸을때
        else:
            flash("등록되지 않은 회원입니다") #userobject가 안받아와질때 == 등록되지 않은 회원일때

    return render_template('login.html')

@app.route('/logout')
def logout():
    session["currentUser"] = '' #로그아웃은 현재 세션(웹브라우저의 작은 공간)에 있는 사용자를 초기화해줌

    return redirect(url_for("login"))


@app.route('/forum', methods = ['GET', 'POST']) #forum 페이지
def forum():
    if request.method == 'GET': #GET의 형태로 접근하면
        global db
        global storage

        id = session["currentUser"] #세션에서 현재 사용자 id를 꺼내오고
        userObject = db.child("user").order_by_child("user_id").equal_to(id).get().val().popitem(last=True) # 그 id를 기반으로 사용자의 정보들을 받아옴
        userNumber = userObject[0]
        userName = userObject[1]["user_name"]
        userImg = storage.child(str(userNumber) + ".jpg").get_url(None) #url의 경우 해당 사용자의 이미지 url을 받아와서 html에서 띄워줌
        messages = db.child("message").get().val()

        profile = {"name": userName, "imgLink": userImg}
        boardData = {"len": len(db.child("message").get().val()), "data": messages}

    return render_template('forum.html', profile=profile, boardData=boardData) #html에 profile과 boarData라는 변수를 보내줘서 화면에 표시하게함

@app.route('/writing', methods = ['GET', 'POST']) #게시글 쓰는 페이지
def writing():
    if request.method == 'POST': #POST형태로 접근하였을때
        global db
        global storage

        id = session["currentUser"] #현재 사용자 id를 불러화서
        userObject = db.child("user").order_by_child("user_id").equal_to(id).get().val().popitem(last=True) #그 id에 해당하는 데이터를 얻는다
        userName = userObject[1]["user_name"]

        subject = request.form["subject"]
        message = request.form["message"]
        file = request.files['file'] #파일을 받아와서

        filename = secure_filename(file.filename) #파일이름을 뽑아내고
        file.save("static/images/" + filename)#프로젝트내의 static의 images 폴더로 저장한다
        uploadUrl = str(filename) #스토리지에 올라갈 파일 이름
        path_local = f"static/images/{filename}" #파일이 로컬에 저장되어 있는 위치
        storage.child(uploadUrl).put(path_local) #스토리지에 올라갈 파일 이름으로 로컬에 있는 파일을 저장함

        db.child("message").push({"subject": subject,
                                  "message": message,
                                  "time": time.strftime('%y-%m-%d'),
                                  "imgUrl": storage.child(filename).get_url(None),
                                  "writer": userName})
        flash("글이 추가되었습니다.")

    return redirect(url_for("forum"))

@app.route('/user', methods = ['GET', 'POST'])
def user(): #유저페이지
    if request.method == 'GET':
        global db
        global storage

        id = session["currentUser"]
        userObject = db.child("user").order_by_child("user_id").equal_to(id).get().val().popitem(last=True)
        userName = userObject[1]["user_name"]
        messages = db.child("message").order_by_child("writer").equal_to(userName).get().val() #현재 사용자가 쓴 글만 뽑아옴


        boardData = {"len": len(db.child("message").get().val()), "data": messages}

    return render_template("user.html", boardData=boardData)

@app.route('/changePassword', methods = ['GET', 'POST']) #실제로 페이지를 보여주지는 않지만 이 주소에서 비밀번호 변경을 처리합니다.
def changePassword(): #비밀번호 변경
    if request.method == 'POST':
        global db
        global storage
        oldPassword = request.form["oldPassword"] #원래 비밀번호
        newPassword = request.form["newPassword"] #새 비밀번호
        newPasswordAgain = request.form["newPasswordAgain"] #새 비밀먼호 확인



        id = session["currentUser"] #현재 사용자 id를 불러오고 사용자 정보들을 불러옴
        userObject = db.child("user").order_by_child("user_id").equal_to(id).get().val().popitem(last=True)
        userName = userObject[1]["user_name"]
        userPassword= userObject[1]["password"]
        userNumber = userObject[0]

        messages = db.child("message").order_by_child("writer").equal_to(userName).get().val()

        if int(oldPassword) != int(userPassword): #만약 기존 비밀번호가 다르면
            flash("이전 비밀번호가 일치하지 않습니다.")
        elif newPassword != newPasswordAgain: # 새 비밀번호가 서로 다르면
            flash("바꿀 비밀번호가 일치하지 않습니다.")
        else: #다 통과하면 비밀번호를 바꿔줌
            db.child("user").child(userNumber).update({"password": int(newPassword)})


    return render_template("login.html") #비밀번호를 바꾸면 login페이지를 띄워줍니다

@app.route('/update', methods = ['GET', 'POST']) #게시글을 업데이트하는 페이지 컨트롤러입니다/
def update():
    if request.method == 'POST': #포스트로 접근하였을시
        global db
        global storage

        subject = request.form["subject"] #html에서 게시글의 제목을 받아오고
        messagesObject = db.child("message").order_by_child("subject").equal_to(subject).get().val().popitem(last=True) #그 제목을 가진 게시글을 불러와서

        messageName = messagesObject[0] #정보를 저장합니다.
        subject = messagesObject[1]["subject"]
        message = messagesObject[1]["message"]
        imgUrl = messagesObject[1]["imgUrl"]
        time = messagesObject[1]["time"]

        data = {"subject": subject, #그리고 그 정보들을 모아 data라는 변수에 저장하고
                "message": message,
                "imgUrl": imgUrl,
                "time": time,
                "messageName": messageName
                }

    return render_template("update.html", data=data) #처음 화면에 띄워줍니다.


@app.route('/updateMessage', methods = ['GET', 'POST']) #메세지를
def updateMessage():
    if request.method == 'POST':
        global db
        global storage

        messageName = request.form["messageName"]
        newSubject = request.form["newSubject"]
        newMessage = request.form["newMessage"]
        newFile = request.files["newFile"]

        filename = secure_filename(newFile.filename)
        newFile.save("static/images/" + filename)
        uploadUrl = str(filename)
        path_local = f"static/images/{filename}"
        storage.child(uploadUrl).put(path_local)

        newUrl = storage.child(filename).get_url(None)

        db.child("message").child(messageName).update({"subject": newSubject})
        db.child("message").child(messageName).update({"message": newMessage})
        db.child("message").child(messageName).update({"imgUrl": newUrl})

    return redirect(url_for('user'))

if __name__ == '__main__':
    # insertData()
    app.run(debug=True)