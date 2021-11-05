# README
## description
2021年２年PD実践 EP302-D3が作ったファームウェア(.ino)とサーバサイドの送受信プログラム(.py)である．
本授業は試作品を作る授業なので，見にくい点も多い．
また，本プログラムの質問等も受け付けません．
### 使用したもの
- [水流センサ](https://ja.aliexpress.com/item/32784530232.html)
- [マイコン](https://ja.aliexpress.com/w/wholesale-wemos-d1-mini.html)
- 私たちが使用したもの
https://www.wemos.cc/en/latest/d1/d1_mini.html
## setup
### install
- リポジトリをclone
`git clone https://github.com/KazumaFujino/EP302-D3-Farm`
- cloneしたディレクトリに移動
`cd ~/***/EP302-D3-Farm`
### microcomputer
- マイコンに書き込み起動
- マイコンのAPに接続して使用したいwifi情報を入力
[wifimangager](https://github.com/tzapu/WiFiManager)を使わせてもらっているので繋げ方はリンクを参照
### server
- サーバサイドプログラムを立ち上げる
`python hosting.py`
## start-up
![](https://i.imgur.com/0mU3wZu.png)
**このように表示されれば成功です!**
`length`の表示の必要はありませんがバッファの作成で必要なので送信する必要はあります．
