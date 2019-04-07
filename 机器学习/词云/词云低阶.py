from wordcloud import WordCloud, STOPWORDS
import matplotlib.pyplot as plt

#加载需要分析的文章
text = open(r'D:\BaiduNetdiskDownload\新建文本文档.txt','r').read()
#创建词云对象并指定格式
stopwords = set(STOPWORDS)
stopwords.add("know")
wc = WordCloud(
        background_color="white",
        width=1000, 
        height=860, 
        max_font_size=300,
        stopwords=stopwords,
        margin=2)

wc.generate(text)
#展示词云
plt.imshow(wc)
plt.axis("off")
plt.show()

#保存词云
wc.to_file('test.png')
