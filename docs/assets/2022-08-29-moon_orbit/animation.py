import matplotlib.pyplot as plt
import matplotlib.patches as patches
from matplotlib.animation import FuncAnimation
import pandas as pd

data = pd.read_csv('result.csv')

fig, ax = plt.subplots()

def update(i):
    # 毎回グラフをクリア
    ax.cla()
    # グラフの設定
    ax.set_xlim(-1.6e8, 1.6e8)
    ax.set_ylim(-1.6e8, 1.6e8)
    ax.set_aspect('equal')
    # 太陽を描き込み
    c = patches.Circle(xy=(0, 0), radius=2e6, ec='black', fc='yellow')
    ax.add_patch(c)
    # プロット
    ax.plot(data['x1'][0:i], data['y1'][0:i], 'b')
    ax.plot(data['x2'][0:i], data['y2'][0:i], 'r')
    ax.plot(data['x1'][i],   data['y1'][i],   'bo', markersize=2)
    ax.plot(data['x2'][i],   data['y2'][i],   'ro', markersize=2)
    # タイトルに経過時間を表示
    ax.set_title('{:g}'.format(data['t'][i]) + ' hours')

ani = FuncAnimation(fig, update, frames=range(data['t'].size),interval=40)
ani.save('result.mp4', writer='ffmpeg', dpi=300)
plt.subplots_adjust(top=0.85)
plt.show()
