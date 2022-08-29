#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <numbers>
// Boostライブラリが必要です
#include <boost/numeric/odeint.hpp>

namespace odeint = boost::numeric::odeint;
using std::endl;
using std::pow;
using std::sqrt;
using std::ofstream;
using std::vector;
using std::string;
using std::string_view;
using std::numbers::pi;

constexpr double G = 8.647e-13;     // 万有引力定数 [km^3/(kg h^2)]

// 微分方程式の実装クラス
class ThreeBody {
private:
    double M;       // 恒星質量
    double m1;      // 惑星質量
    double m2;      // 衛星質量

public:
    using state = std::array<double, 8>;
    ThreeBody(double M, double m1, double m2) {
        this->M = M;
        this->m1 = m1;
        this->m2 = m2;
    }
    void operator()(const state& x, state& dx, double t) {
        double r_me = pow(x[0] - x[2], 2.) + pow(x[1] - x[3], 2.);
        double r_es = pow(x[0], 2.) + pow(x[1], 2.);
        double r_ms = pow(x[2], 2.) + pow(x[3], 2.);
        // 位置座標の微分＝速度 dx1 / dt = u1
        dx[0] = x[4];
        dx[1] = x[5];
        dx[2] = x[6];
        dx[3] = x[7];
        // 速度の微分＝加速度 運動方程式を実装
        dx[4] = - G * m2 / pow(r_me, 1.5) * (x[0] - x[2]) - G * M / pow(r_es, 1.5) * x[0];
        dx[5] = - G * m2 / pow(r_me, 1.5) * (x[1] - x[3]) - G * M / pow(r_es, 1.5) * x[1];
        dx[6] = - G * m1 / pow(r_me, 1.5) * (x[2] - x[0]) - G * M / pow(r_ms, 1.5) * x[2];
        dx[7] = - G * m1 / pow(r_me, 1.5) * (x[3] - x[1]) - G * M / pow(r_ms, 1.5) * x[3];
    }
};

// 出力クラス
class Output {
private:
    ofstream ofs;

public:
    using state = TwoBody::state;
    Output(string_view strFile) {
        ofs = ofstream(strFile.data());
        if (!ofs) {
            throw std::runtime_error("Error: Cannnot open output file.");
        }
        ofs << std::fixed << std::setprecision(16);
        ofs << "t,x1,y1,x2,y2" << endl;
    }
    void operator()(const state& x, double t){
        ofs << t << "," << x[0] << "," << x[1] << "," << x[2] << "," << x[3] << endl;
    }
};

int main() {
    double mu = 0.0123002;      // 月-地球質量比 [1]
    double M_e = 5.97e24;       // 地球質量 [kg]
    double M_s = 1.99e30;       // 太陽質量 [kg]
    double M_m = M_e * mu;      // 月質量 [kg]
    double R_me = 384000;       // 月-地球距離 [km]
    double R_es = 1.4959787e8;  // 地球-太陽距離 [km]
    double T = 27.3217 * 24.;   // 周期 [h]
    double v_e = 2. * pi * R_me * mu / ((mu + 1.) * T);     // 地球速さ [km/h]
    double v_m = 2. * pi * R_me / ((mu + 1.) * T);          // 月速さ [km/h]
    double V = 2. * pi * R_es / (365. * 24.);               // 地球公転速さ [km/h]

    try {
        // 実装した微分方程式をインスタンス化
        ThreeBody threebody = ThreeBody(M_s, M_e, M_m);
        // 初期値
        ThreeBody::state State = { R_me * mu / (mu + 1.) + R_es, 0., -R_me / (mu + 1.) + R_es, 0., 0., v_e + V, 0., -v_m + V };
        // 4階のルンゲ・クッタ法で解く
        odeint::runge_kutta4<ThreeBody::state> Stepper;
        // 出力をインスタンス化
        Output output = Output("result.csv");
        // 実際に計算
        odeint::integrate_const(Stepper, threebody, State, 0., 24. * 365., 6., std::ref(output));
        // 期間・刻み幅を変えたバージョン
        // odeint::integrate_const(Stepper, threebody, State, 0., 24. * 30., 1., std::ref(output));
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}