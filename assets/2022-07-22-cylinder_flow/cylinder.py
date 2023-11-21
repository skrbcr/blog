import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
from scipy.misc import derivative   # 関数の微分を計算

# 定数
A = 1   # 円柱半径
U = 1   # 定常流の速さ

LOW = -4.       # 4. or 2.
HIGH = 4.
N = 128          # 128 or 24

# 複素ポテンシャル
fn_f = lambda z: U * z + U * np.power(A, 2) / z
# 渦糸追加
#fn_f = lambda z: U * (z + A * A / z) + complex(0, 1) * 1 * U * np.log(z)
        # 小：1　中：2　大：3

def f_vel(x: float, y: float) -> tuple:
    """
    位置(x, y)での速度を返す
    """
    z = complex(x, y)
    df = derivative(fn_f, z, 1.0E-6)
    return df.real, -df.imag

def calc():
    # メッシュ
    x, y = np.meshgrid(np.linspace(LOW, HIGH, N), np.linspace(LOW, HIGH, N))
    u, v = np.meshgrid(np.zeros(N), np.zeros(N))
    # 複素ポテンシャルから速度を計算
    for i in range(N):
        for j in range(N):
            if np.power(x[i][j], 2) + np.power(y[i][j], 2) >= np.power(A, 2):
                u[i][j], v[i][j] = f_vel(x[i][j], y[i][j])
    # グラフ描画
    fig, ax = plt.subplots()
    # 円筒を描き入れ
    c = patches.Circle(xy=(0, 0), radius=1, ec='red', fc='white')
    ax.add_patch(c)
    # Stream Plot
    ax.streamplot(x, y, u, v)
    # Quiver
    # ax.quiver(x, y, u, v)
    ax.set_aspect('equal')
    plt.show()

calc()