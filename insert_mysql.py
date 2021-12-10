import MySQLdb,datetime,sys
from http.server import BaseHTTPRequestHandler, HTTPServer

# util デバッグ用
debug = False#プリント関数を実行し，sql処理をしないか

def sql_p(sentence):
    if(debug):
        print(sentence)
def cursor_exe(sql):
    if(not debug):
        cursor.execute(sql)

# データベースへの接続とカーソルの生成
connection = MySQLdb.connect(
    host='localhost',
    user='root',
    passwd='1234',
    db='watersensor_user',
    charset='utf8')
cursor = connection.cursor()

# ユーザ名を入力
print("あなたの名前:", end='')
name = input()
#name = "kazuma"

# テーブル処理
sql = "CREATE TABLE IF NOT EXISTS "+name+"""(
    datetime datetime,
    amount DOUBLE
    )"""
cursor_exe(sql)
sql_p(sql)

# HTTPリクエスト -> 処理
class Client(BaseHTTPRequestHandler):

    def do_POST(self):
        dt_now = datetime.datetime.now()
        content_len = int(self.headers.get('content-length'))
        body = b'OK'
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.send_header('Content-length', len(body))
        self.end_headers()
        self.wfile.write(body)
        requestBody = self.rfile.read(content_len).decode('ascii')
        print("body = " + requestBody)
        #print("length = " + str(content_len))

        sql = "INSERT INTO "+name+" VALUES ("+dt_now.strftime('%Y%m%d%H%M%S')+","+requestBody+")"
        cursor_exe(sql)
        sql_p(sql)
        connection.commit() #dbにセーブ

server = HTTPServer(('', 80), Client)
server.serve_forever()

connection.close() # db接続を閉じる
