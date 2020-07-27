import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt   #그래프 출력시
import matplotlib as mpl    #그래프 옵션
import warnings

from matplotlib.animation import FuncAnimation

warnings.filterwarnings('ignore')

plt.style.use('default')

#그래프의 한글설정
mpl.rc('font',family='Malgun Gothic')

#그래프의 한글을 더욱 선명하게 출력
from IPython.display import set_matplotlib_formats
set_matplotlib_formats('retina')

#그래프에서 음수 값이 나올 때, 깨지는 현상 방지
mpl.rc('axes',unicode_minus=False)
import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt   #그래프 출력시
import matplotlib as mpl    #그래프 옵션
import warnings
warnings.filterwarnings('ignore')
plt.style.use('default')
#그래프 시각화 옵션 설정함수
#그래프의 한글설정
mpl.rc('font',family='Malgun Gothic')
#그래프의 한글을 더욱 선명하게 출력
from IPython.display import set_matplotlib_formats
set_matplotlib_formats('retina')
#그래프에서 음수 값이 나올 때, 깨지는 현상 방지
mpl.rc('axes',unicode_minus=False)

corona=pd.read_csv('new_case_trends__united_states.csv')
nasdak=pd.read_csv('NQ=F (1).csv')
#Date를 str타입에서 datetime타입으로 변환
corona['Date']=pd.to_datetime(corona['Date'])
#분석기간내 데이터만 추출
corona=corona[(corona['Date']>='2020-02-01')&(corona['Date']<='2020-07-06')].reset_index(drop=True)
#Date를 str타입에서 datetime타입으로 변환
nasdak['Date']=pd.to_datetime(nasdak['Date'])
#분석기간내 데이터만 추출
nasdak=nasdak[(nasdak['Date']>='2020-02-01')&(nasdak['Date']<='2020-07-06')].reset_index(drop=True)

def data_gen():
    t = data_gen.t
    cnt = 0
    while cnt < 1000:
        cnt+=1
        t += 0.05
        y1 = np.sin(2*np.pi*t) * np.exp(-t/10.)
        y2 = np.cos(2*np.pi*t) * np.exp(-t/10.)
        # adapted the data generator to yield both sin and cos
        yield t, y1, y2

data_gen.t = 0

fig,ax=plt.subplots(figsize=(8,6))
ax.plot(corona['Date'],corona['New Cases'],color='red')
ax.set_xlabel('Time')
ax.set_ylabel('Corona New Cases',color='red')
ax.tick_params('y',colors='red')

ax2=ax.twinx()
ax2.plot(nasdak['Date'],nasdak['Adj Close'],color='blue')
ax2.set_ylabel('NASDAQ',color='blue')
ax2.tick_params('y',colors='blue')

x_data = []
y_data = []

def animation_frame()

animation = FuncAnimation(fig)