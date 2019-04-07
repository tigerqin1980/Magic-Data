import jieba
from PIL import Image  
import numpy as np  
import matplotlib.pyplot as plt  
from wordcloud import WordCloud, STOPWORDS  
import os

os.chdir('C:\D')
#读取txt文件并进行分词
text = open(r'C:\Users\o\Documents\WeChat Files\ozq1029\Files\数据.txt','r',encoding='utf-8').read()
wordlist_after_jieba = jieba.cut(text, cut_all=False)
wl_space_split = " ".join(wordlist_after_jieba)
print('分词成功')

# read the mask image  
mask = np.array(Image.open( r'C:\Users\o\Desktop\timg.jpg'))    
print('加载图片成功！')

#可以加多个屏蔽词
stopwords = set(STOPWORDS)
stopwords.add("此用户没有填写评价")

#创建词云对象
wc = WordCloud(  
    #设置字体，不指定就会出现乱码 
    font_path=r'C:\Windows\Fonts\STHUPO.ttf',  
    background_color="white",   
    max_words=20000,   
    mask=mask,  
    stopwords=stopwords,
    max_font_size=50,
    random_state=30
    # 设置有多少种随机生成状态，即有多少种配色方案
    )  
      
# generate word cloud  
wc.generate(text)  
  
# store to file  
wc.to_file( "词云图.png")

# show  
plt.imshow(wc, interpolation='bilinear')  
plt.axis("off")
#不显示坐标轴  
plt.figure()  
plt.imshow(mask, cmap=plt.cm.gray, interpolation='bilinear')  
plt.axis("off")  
plt.show()  
print('生成词云成功!')