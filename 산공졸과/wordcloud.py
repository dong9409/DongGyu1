# wordcloud = WordCloud(
#     font_path='C:/Windows/Fonts/NANUMGOTHIC.TTF',
#     width=1200,
#     height=1200,
#     background_color="white"
# )
#
# # keywords.pop('삭제된')  # 이상한 값들 제거
# # keywords.pop('댓글입니다.')
# # keywords.pop('처리중입니다')
#
# # wordcloud = wordcloud.generate_from_text(text)
# wordcloud = wordcloud.generate_from_frequencies(keywords)
#
# def __array__(self):
#     """Convert to numpy array.
#     Returns
#     -------
#     image : nd-array size (width, height, 3)
#         Word cloud image as numpy matrix.
#     """
#     return self.to_array()
#
#
# def to_array(self):
#     """Convert to numpy array.
#     Returns
#     -------
#     image : nd-array size (width, height, 3)
#         Word cloud image as numpy matrix.
#     """
#     return np.array(self.to_image())
#
# array = wordcloud.to_array()
# print(type(array)) # numpy.ndarray
# print(array.shape) # (, 800, 3)
#
# fig = plt.figure(figsize=(10, 10))
# plt.imshow(array, interpolation="bilinear")
# plt.axis("off")
# plt.show()
# fig.savefig('자유게시판.png')
