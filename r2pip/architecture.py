import r2pipe

def find64(start, arc, str2):
    f = open(f"find64_{arc}_all.txt", 'w')
    for begin in range(0,len(str2), 16):
        if(begin != len(str2)-8):
            segment = str2[begin:begin+16]
            f.write(f"address: 0x{start+begin//2:08x}")
            f.write('\n')
            f.write(segment)
            f.write('\n')
            f.write(r.cmd(f"rasm2 -a {arc} -b 64 -e -d {segment}"))
    f.close()

def find32(start, arc, str2):
    f = open(f"find32_{arc}_all.txt", 'w')
    for begin in range(0,len(str2), 8):
        if(begin != len(str2)-4):
            segment = str2[begin:begin+8]
            f.write(f"address: 0x{start+begin//2:08x}")
            f.write('\n')
            f.write(segment)
            f.write('\n')
            f.write(r.cmd(f"rasm2 -a {arc} -b 32 -e -d {segment}"))
    f.close()

def find16(start, arc, str2):
    f = open(f"find16_{arc}_all.txt", 'w')
    for begin in range(0,len(str2), 4):
        if(begin != len(str2)-2):
            segment = str2[begin:begin+4]
            f.write(f"address: 0x{start+begin//2:08x}")
            f.write('\n')
            f.write(segment)
            f.write('\n')
            f.write(r.cmd(f"rasm2 -a {arc} -b 16 -e -d {segment}"))
    f.close()

if __name__ == "__main__":
    r = r2pipe.open("gcc_mips64")
    arc = "ppc"
    r.cmd("aa")
    sz = 10000
    if sz%16!=0:
        c = sz // 16
        sz = 16*(c+1)

    s = r.cmd(f"px {sz}")
    str_list = s.split("\n")
    temp = str_list[1].split()
    start = int(temp[0], 16)

    str2 = ""
    for i in str_list[1:len(str_list)-1]:
        temp1 = i.split()
        for j in range(1, 9):
            str2 = str2 + temp1[j]

    find64(start, arc, str2)
    find32(start, arc, str2)

