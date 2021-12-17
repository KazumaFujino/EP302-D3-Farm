## description
2021年２年PD実践 EP302-D3が作ったファームウェア(.ino)とサーバサイドの送受信プログラム(.py)である．<br>
本授業は試作品を作る授業なので，見にくい点も多い．また，本プログラムの質問等も受け付けません．
### 使用したもの
- [水流センサ](https://ja.aliexpress.com/item/32784530232.html)
- [マイコン](https://ja.aliexpress.com/w/wholesale-wemos-d1-mini.html)
- 私たちが使用したもの
https://www.wemos.cc/en/latest/d1/d1_mini.html
## hardware
![](https://i.imgur.com/y0MG0cK.png)
`hardware/`のstlファイルを参照
## structure
![](https://i.imgur.com/E5bUtvi.png)
## setup
### server
- リポジトリをクローン<br>
`git clone https://github.com/KazumaFujino/EP302-D3-Farm`
- mysql57をインストール<br>
`CREATE DATABASE watersensor_user;`
- pythonパッケージをインストール<br>
`pip -m install MySQLdb datetime sys httpserver matplotlib`
### microcomputer
- マイコンに書き込み起動<br>
- マイコンのAPに接続して使用したいwifi情報を入力<br>
[wifimangager](https://github.com/tzapu/WiFiManager)を使わせてもらっているので繋げ方はリンクを参照
## start-up
- pythonプログラムを立ち上げる<br>
`python insert_mysql plot_mysql`
- ユーザ名を入力
