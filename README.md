## description
2021年2年PD実践 EP302-D3が作ったファームウェア(.ino)とサーバサイドの送受信プログラム(.py)である．<br>
本授業は試作品を作る授業なので，見にくい点も多い．
また，本プログラムの質問等も受け付けません．
### 使用したもの
- [水流センサ](https://ja.aliexpress.com/item/32784530232.html)
- [arduinoボード](https://ja.aliexpress.com/w/wholesale-wemos-d1-mini.html)
- ESP8266
- 私たちが使用した開発ボード<br>
https://ja.aliexpress.com/item/32651747570.html
## setup
### install
- リポジトリをclone<br>
`git clone https://github.com/KazumaFujino/EP302-D3-Farm`
- arduino ideをインストール<br>
https://www.arduino.cc/en/software
### microcomputer
- ideにマイコンを認識させる<br>
http://ahoministrator.sakura.ne.jp/retrospective/archives/1048
- .inoをマイコンに書き込み起動
- マイコンのAPに接続して使用したいwifi情報を入力<br>
[wifimangager](https://github.com/tzapu/WiFiManager)を使わせてもらっているので繋げ方はリンクを参照
### server
- pythonプログラムの実行に必要なパッケージをインストール<br>
`pip install httpserver`
- サーバサイドプログラムを立ち上げる<br>
`python hosting.py`
## start-up
![](https://i.imgur.com/0mU3wZu.png)
**このように表示されれば成功です!**<br>
※`length`の表示の必要はありませんがバッファの作成で必要なので送信する必要はあります．
