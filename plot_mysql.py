import MySQLdb
import matplotlib.pyplot as plt

# util デバッグ用
debug = False #プリント関数を実行するか

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
sql = "SELECT * FROM "+name#" limit 5"
cursor_exe(sql)
sql_p(sql)

date_array  = []
amount_array = []

#終値がゼロ（取引がない）ときを除いて、データを配列に格納する。
for row in cursor.fetchall():
    date_array.append(row[0])
    amount_array.append(row[1])

plt.plot(date_array,  amount_array)
plt.show()

cursor.close() #カーソルを閉じる
connection.close() # db接続を閉じる
