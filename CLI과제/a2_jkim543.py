#!/usr/bin/env python3

'''
Docstring: Enter your header and Documentation Here

'''

import os
import sys
import time
import argparse
import subprocess

args = object()  # arguments will be returned here from parse_command_args()

def parse_command_args():  # provided
    "Calls argumentparser, and returns an object"
    # TODO: one add_argument line is missing. Refer to documentation and implement it.
    parser = argparse.ArgumentParser(description="Usage Report based on the last command",epilog="Copyright 2020 - Eric Brauer")
    parser.add_argument("-l", "--list", type=str, choices=['user','host'], help="generate user name or remote host IP from the given files")
    parser.add_argument("-r", "--rhost", help="usage report for the given remote host IP")
    parser.add_argument("-u", "--user", help="usage report for the given user name")
    #아래 라인을 추가하여 타입에 대한 정보를 받도록 하였습니다.
    parser.add_argument("-t","--type", type=str, choices=['daily','monthly'],help="choose the type")
    parser.add_argument("-s", "--seconds", action="store_true", help="return times in seconds")
    parser.add_argument("-v","--verbose", action="store_true",help="turn on output verbosity")
    parser.add_argument("files",metavar='F', type=str, nargs='+',help="list of files to be processed")
    args=parser.parse_args()
    if args.verbose:
        print('Files to be processed:',args.files)
        print('Type of args for files',type(args.files))
        if args.user:
            print('usage report for user:',args.user)
        if args.rhost:
            print('usage report for remote host:',args.rhost)
        if args.type:
            print('usage report type:',args.type)
    return args

def open_file_list():  # provided?
    "opens each file from args, and returns a list of lines"
    output = []
    filename_list = args.files
    if 'F' in filename_list:  # we're going to ignore this
        filename_list.remove('F')
    #TODO: if args.files contains 'online', use Popen to call `last -Fiw`  
    for filename in args.files:  # several files could be specified
        f = open(filename, 'r')
        output = f.read().split('\n')
        f.close()
    return output  # this is a LIST

def parse_for_user(file_line_list):  # provided
    "call this function when 'a2_<st_id>.py -l user'"
    return_set = set()  # quick and dirty way of ignoring repeats    
    for line in file_line_list:
        if line == '':  # if the line is empty, ignore it
            pass
        else:
            splitted = line.split()  # split the line by whitespace
            return_set.add(splitted[0])  # first item in the splitted is user 
    return_list = list(return_set)  # convert this to a list, and
    return_list.sort()  # sort alphabetically
    return return_list

def parse_for_host(file_line_list):  # definition specified
    "call this function when 'a2_<st_id>.py -l host'"
    # TODO: complete the function
    return_list = []
    return_set = set()  # quick and dirty way of ignoring repeats
    for line in file_line_list:
        if line == '':  # if the line is empty, ignore it
            pass
        else:
            splitted = line.split()  # split the line by whitespace
            return_set.add(splitted[2])  # first item in the splitted is user
    return_list = list(return_set)  # convert this to a list, and
    return_list.sort()  # sort alphabetically
    return return_list

def parse_for_daily(output_list, user):  # pseudo provided
    "call this when user uses -u/r <user/ip> -t daily"
    return_dict = {}
    for line in output_list:
        splitted = line.split()
        if line == '':
            pass
        elif splitted[0] == user or splitted[2] == user:
            info = extract_date(line)
            date = f"{info[0][2]}/{info[0][1]}/{info[0][0]}"
            using_time = time.mktime(info[1]) - time.mktime(info[0])

            if date == None:
                pass
            if date in return_dict:
                return_dict[date].append(using_time)
            else:
                return_dict[date] = [using_time]
    return return_dict

    # for each line in output list:
    # if it's empty, ignore it.
    # use extract_date to get the start date and stop date.
    # if extract_date returns nothing, ignore it.
    # otherwise, get the duration.
    # if that particular start date DD/MM/YYYY is already a key in return_dict,
    # then add duration to the value of that key.
    # otherwise, add DD/MM/YYYY as a key and duration as the value.
    # return dict should look like this: 
    # {'01/01/1980': '3200', '02/01/1980': '1600', etc. ]

def extract_date(line):  # provided
    "get dates from a line of output"
    if line == '':
        return None
    else:
        outlist = []  # outlist is going to return both dates in a list
        splitted = line.split()
        first_date = splitted[4:8]
        second_date = splitted[10:14]
        t_in = " ".join(first_date)
        t_out = " ".join(second_date)
        try:
            fmt="%b %d %H:%M:%S %Y"
            time_in = time.strptime(t_in, fmt)
            time_out = time.strptime(t_out, fmt)
            outlist.append(time_in)
            outlist.append(time_out)
        except:
            return None
        return outlist

def return_date_str(date_object):  # provided
    "take in date object, return as string in DD/MM/YYYY"
    fmt="%d/%m/%Y"
    return str(time.strftime(fmt, date_object))

def return_duration_secs(start_time, stop_time):  # provided
    "take two date objects, return the difference between them in seconds"
    fl_stop = int(time.strftime("%s", stop_time))
    fl_start = int(time.strftime("%s", start_time))
    return fl_stop - fl_start

if __name__ == "__main__":
    args = parse_command_args()
    # parse_for_user("usage_data_file.txt")
    output = open_file_list()
    # check args.user

    if args.list == "user": #args.list에 user값이 들어오면 usr목록을 출력합니다.
        print("User list for usage_data_file")
        print("=============================")
        for user in parse_for_user(output):
            print(user)

    elif args.list == "host": #args.list에 host값이 들어오면 host 목록읠 출력합니다.
        print("Host list for usage_data_file")
        print("=============================")
        for host in parse_for_host(output):
            print(host)

    if args.user != None: #args.user에 값이 아래와 같이 동작합니다.
        total = 0
        if args.type == "daily": #type에 daily 값이 들어왔을때 일별 사용량을 출력합니다.
            print(f"Daily Usage Report for {args.user}")
            print("============================")
            print("Date\t\tUsage")
            dic = parse_for_daily(output, args.user)
            for (key, value) in dic.items():
                for v in value:
                    if args.seconds == True:
                        print(f"{key}\t {int(v)}")
                    elif args.seconds == False:
                        print(f"{key}\t {time.strftime('%H:%M:%S', time.gmtime(int(v)))}")
                    total += v
            if args.seconds == True: #seconds 값이 true 일 경우 초 단위로 출력합니다
                print(f"Total\t\t {int(total)}")
            elif args.seconds == False: #seconds 값이 false 일 경우 HHMMSS 형태로 출력합니다.
                print(f"Total\t\t {time.strftime('%H:%M:%S', time.gmtime(total))}")

        elif args.type == "monthly": #type에 monthly 값이 들어왔을때 월별 사용량을 출력합니다.
            print(f"Monthly Usage Report for {args.user}")
            print("============================")
            print("Date\t\t Usage")
            month_dic = {}
            dic = parse_for_daily(output, args.user)

            for (key, value) in dic.items():
                splitted = key.split('/')
                mmyy = f"{splitted[1]}/{splitted[2]}"
                if mmyy in month_dic:
                    temp = 0
                    for v in value:
                        temp += v
                    month_dic[mmyy] += temp
                else:
                    temp = 0
                    for v in value:
                        temp += v
                    month_dic[mmyy] = temp

            for (key, value) in month_dic.items():
                if args.seconds == True: #seconds 값이 true 일 경우 초 단위로 출력합니다
                    print(f"{key}\t\t {int(value)}")
                elif args.seconds == False: #seconds 값이 false 일 경우 HHMMSS 형태로 출력합니다.
                    print(f"{key}\t\t {time.strftime('%H:%M:%S', time.gmtime(int(value)))}")
                total += value

            if args.seconds == True:  #seconds 값이 true 일 경우 초 단위로 출력합니다
                print(f"Total\t\t {int(total)}")
            elif args.seconds == False: #seconds 값이 false 일 경우 HHMMSS 형태로 출력합니다.
                print(f"Total\t\t {time.strftime('%H:%M:%S', time.gmtime(int(total)))}")


    elif args.rhost != None: #인자로 rhost 값이 들어 왔을 때 rhost의 일별 사용량, 월별 사용량을 출력합니다.
        print(f"Daily Usage Report for {args.rhost}")
        print("============================")
        print("Date\t\tUsage")
        total = 0
        if args.type == "daily":
            dic = parse_for_daily(output, args.rhost)
            for (key, value) in dic.items():
                for v in value:
                    splitted = key.split('/')
                    print(f"{splitted[2]} {splitted[1]} {splitted[0]}\t{int(v)}")
                    total += v
            print(f"Total\t\t{int(total)}")

        elif args.type == "monthly":
            month_dic = {}
            dic = parse_for_daily(output, args.rhost)

            for (key, value) in dic.items():
                splitted = key.split('/')
                mmyy = f"{splitted[1]}/{splitted[2]}"
                if mmyy in month_dic:
                    temp = 0
                    for v in value:
                        temp += v
                    month_dic[mmyy] += temp
                else:
                    temp = 0
                    for v in value:
                        temp += v
                    month_dic[mmyy] = temp

            for (key, value) in month_dic.items():
                if args.seconds == True:
                    print(f"{key}\t\t {int(value)}")
                elif args.seconds == False:
                    print(f"{key}\t\t {time.strftime('%H:%M:%S', time.gmtime(int(value)))}")
                total += value

            if args.seconds == True:
                print(f"Total\t\t {int(total)}")
            elif args.seconds == False:
                print(f"Total\t\t {time.strftime('%H:%M:%S', time.gmtime(int(total)))}")

