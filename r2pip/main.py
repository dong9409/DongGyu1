import r2pipe

def is_branch(second, branch):
    second = second.split()
    for inst in branch:
        if inst == second[0]:
            return True
    return False

def find64(start, str2, arc, target, branch):
    f = open(f"find64_{arc}.txt", 'w')
    for begin in range(8, len(str2), 16):
        if begin < len(str2) - 16:
            first_segment = str2[begin:begin + 16]
            second_segment = str2[begin+16:begin + 32]
            if arc == "ppc" or arc == "mips":
                first = r.cmd(f"rasm2 -a {arc} -b -e 64 -d {first_segment}")
                second = r.cmd(f"rasm2 -a {arc} -b -e 64 -d {second_segment}")
            elif arc == "arm":
                first = r.cmd(f"rasm2 -a {arc} -b 64 -d {first_segment}")
                second = r.cmd(f"rasm2 -a {arc} -b 64 -d {second_segment}")

            if target in first and is_branch(second, branch):
                f.write(f"address: 0x{start + begin // 2:08x}")
                f.write('\n')
                f.write(first_segment)
                f.write('\n')
                f.write(first)

                f.write(f"address: 0x{start + (begin+16) // 2:08x}")
                f.write('\n')
                f.write(second_segment)
                f.write('\n')
                f.write(second)
    f.close()

def find32(start, str2, arc, target, branch):
    f = open(f"find32_{arc}.txt", 'w')
    for begin in range(4, len(str2), 8):
        if begin < len(str2) - 8:
            first_segment = str2[begin:begin + 8]
            second_segment = str2[begin+8:begin + 16]
            first = ""
            second = ""
            if arc == "ppc" or arc == "mips":
                first = r.cmd(f"rasm2 -a {arc} -b -e 32 -d {first_segment}")
                second = r.cmd(f"rasm2 -a {arc} -b -e 32 -d {second_segment}")
            elif arc == "arm":
                first = r.cmd(f"rasm2 -a {arc} -b 32 -d {first_segment}")
                second = r.cmd(f"rasm2 -a {arc} -b 32 -d {second_segment}")

            if target in first and is_branch(second, branch):
                f.write(f"address: 0x{start + begin // 2:08x}")
                f.write('\n')
                f.write(first_segment)
                f.write('\n')
                f.write(first)

                f.write(f"address: 0x{start + (begin+8) // 2:08x}")
                f.write('\n')
                f.write(second_segment)
                f.write('\n')
                f.write(second)
    f.close()


def find16(start, str2, arc, target, branch):
    f = open(f"find16_{arc}.txt", 'w')
    for begin in range(0, len(str2), 4):
        if begin != len(str2) - 2:
            first_segment = str2[begin:begin + 4]
            second_segment = str2[begin + 4:begin + 8]
            first = ""
            second = ""
            if arc == "ppc" or arc == "mips":
                first = r.cmd(f"rasm2 -a {arc} -b -e 16 -d {first_segment}")
                second = r.cmd(f"rasm2 -a {arc} -b -e 16 -d {second_segment}")
            elif arc == "arm":
                first = r.cmd(f"rasm2 -a {arc} -b 16 -d {first_segment}")
                second = r.cmd(f"rasm2 -a {arc} -b 16 -d {second_segment}")


            if target in first and is_branch(second, branch):
                f.write(f"address: 0x{start + begin // 2:08x}")
                f.write('\n')
                f.write(first_segment)
                f.write('\n')
                f.write(first)


                f.write(f"address: 0x{start + (begin+4) // 2:08x}")
                f.write('\n')
                f.write(second_segment)
                f.write('\n')
                f.write(second)
    f.close()

if __name__ == "__main__":
    file_name = input("파일명을 입력하세요:")
    mode = int(input("아키텍처를 고르세요 \n1. ARM    2. MIPS   3.PowerPC\n"))
    target = input("찾을 명령어 또는 레지스터를 입력하세요 : \n")
    print("분석중...")

    r = r2pipe.open(file_name)
    r.cmd("aa")

    sz = int(r.cmd("afl+"))
    sz = 10000
    if sz % 16 != 0:
        c = sz // 16
        sz = 16 * (c + 1)
    s = r.cmd(f"px {sz}")


    str_list = s.split("\n")
    temp = str_list[1].split()
    start = int(temp[0], 16)
    str2 = ""
    for i in str_list[1:len(str_list) - 1]:
        temp1 = i.split()
        for j in range(1, 9):
            str2 = str2 + temp1[j]

    arc = "arm" #default는 arm
    if mode == 1:
        arc = "arm"
        branch = ["b", "bl", "bx", "blx", "bne", "beq", "cmp", "br"]
        find32(start, str2, arc, target, branch)
        # find16(start, str2, arc, target, branch)
    elif mode == 2:
        arc = "mips"
        branch = ["beq", "bne", "j", "jr", "jal"]
        find64(start, str2, arc, target, branch)
        find32(start, str2, arc, target, branch)
    elif mode == 3:
        arc = "ppc"
        branch = ["b", "bl", "blr", "blt", "ba", "bla", "bc", "bca", "bcl", "bcla", "bclr", "bclrl"]
        find64(start, str2, arc, target, branch)
        find32(start, str2, arc, target, branch)


