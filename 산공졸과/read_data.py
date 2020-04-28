from selenium import webdriver
from bs4 import BeautifulSoup
from collections import defaultdict
import time
import datetime
import os
import json
import matplotlib.pyplot as plt
import pandas as pd
import os
import json
from konlpy.tag import Hannanum
import re
from krwordrank.word import KRWordRank
import requests

def search(dirname):  # 디렉토리 속 파일 경로 리스트 가져오기 ex : ./Result/file.txt
    file_name_list = list()
    filenames = os.listdir(dirname)
    for filename in filenames:
        full_filename = os.path.join(dirname, filename)
        file_name_list.append(full_filename)
    return file_name_list


def file_read(file_name_list):  # json 으로 해당 경로 파일 가져오기
    data = list()
    for file_path in file_name_list:
        with open(file_path, 'r') as file_point:
            data.append(json.load(file_point))
    return data

#makefile

file_list = search('C:/Users/dong9/PycharmProjects/everytime/data/')
data = file_read(file_list)
data = sorted(data , key = lambda d: (d['now_time']))

df = pd.DataFrame(columns=['time', 'address', 'title', 'text'])

for i in data:
    df = df.append(pd.DataFrame([{'time': i['now_time'], 'address': i['url'], 'title': i['title'], 'text': i['text']}]))
# df = df.sort_values(by=['time'], axis=0)
df.to_csv('Crawling.csv', index=False, mode='a', encoding='utf-8-sig', header=True)



# #Rank추출
# wordrank_extractor = KRWordRank(
#     min_count=10,  # 단어의 최소 출현 빈도수 (그래프 생성 시)
#     max_length=15,  # 단어의 최대 길이
#     verbose=True
# )
#
# beta = 0.85  # PageRank의 decaying factor beta
# max_iter = 10
#
# input_text = str()
# text = list()
# for content in data:
#     text.append(content['title'])
#     text.append(content['text'])
#
#     # for comment in content['comment_text']:
#     #     text.append(comment)


# input_text = ' '.join(text)
#
# #필요없는 문자 제거 빈도수 체크
# input_text = re.sub('[0-9]+', '', input_text)
# input_text = re.sub('[A-Za-z]+', '', input_text)
# input_text = re.sub('[-=+,#/\:$.@*\"※~&%ㆍ·!』\\‘’|\(\)\[\]\<\>`\'…》]', '', input_text)
#
# print(input_text)
#
# hannanum = Hannanum()
# text_list = hannanum.nouns(input_text)
# word_list = pd.Series(text_list)
# result = word_list.value_counts().head(20)
# print(word_list) #word_list랑 input_text랑 비교해보기

# df_rank = pd.DataFrame(columns=['Word', 'Rank_Value'])
#
# keywords = None
# rank = ''
# graph = None
# keywords, rank, graph = wordrank_extractor.extract(text, beta, max_iter)
#
# word_list = list()
#
# for word, r in sorted(keywords.items(), key=lambda x:x[1], reverse=True)[:60]:
#     print('%8s:\t%.4f' % (word, r))
#     word_list.append((word, r))
#
# print(input_text)
# df_rank = pd.DataFrame(word_list, columns = ['Word', 'Rank_Value'])
# df_rank.to_csv('WordRank.csv', index=False, mode='a', encoding='utf-8-sig', header=True)
