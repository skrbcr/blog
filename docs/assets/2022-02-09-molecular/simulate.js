// 描画関係
const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");

// フレームカウンタ
let fcount = 0;

// 位置座標
let x_1 = 0;
let x_2 = 0;
let x_3 = 0;

// 定数
const omeg_1 = 1 / 15;
const omeg_2 = Math.sqrt(11/3) / 15;

// 任意定数（振幅）
let C_1 = 0;
let C_2 = 0;

window.onload = function(){
    C_1 = 1;
    C_2 = 0.2;

    main();
}

function main() {
    // 画面クリア
    ctx.clearRect(0,0,canvas.width,canvas.height);

    // 計算・描画
    calc();
    drawRect(300 + 30 * x_1, 295, 300 + 30 * (x_2 - x_1), 10, "#FFFFFF");
    drawRect(600 + 30 * x_2, 295, 300 + 30 * (x_3 - x_2), 10, "#FFFF00");
    drawCircle(300 + 30 * x_1, 300, 50, "#FF0000");
    drawCircle(600 + 30 * x_2, 300, 50, "#00AA00");
    drawCircle(900 + 30 * x_3, 300, 50, "#FF0000");

    // アニメーション
    requestAnimationFrame(main);

    fcount++;
}

// 長方形を描画
function drawRect(x, y, width, height, strColor) {
    ctx.beginPath();
    ctx.rect(x, y, width, height);
    ctx.fillStyle = strColor;
    ctx.closePath();
    ctx.fill();
}

// 円を描画
function drawCircle(x,y,r,strColor) {
    ctx.beginPath();
    ctx.arc(x,y,r,0,2*Math.PI,true);
    ctx.fillStyle = strColor;
    ctx.closePath();
    ctx.fill();
}

// 計算の中身
function calc() {
    x_1 = C_1 * Math.cos(omeg_1 * fcount) + C_2 * Math.cos(omeg_2 * fcount);
    x_2 = - (8/3) * C_2 * Math.cos(fcount * Math.sqrt(11/3) / 15);
    x_3 = - C_1 * Math.cos(omeg_1 * fcount) + C_2 * Math.cos(omeg_2 * fcount);
}

// 新しい数値を取得
function changeVars() {
    C_1 = document.getElementById("c1").value;
    C_2 = document.getElementById("c2").value;
}