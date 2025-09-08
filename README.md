1. 新しいブランチを作成して切り替え
```bash
git checkout -b <ブランチ名>
e.g.) git checkout -b feature/readme
```

2. 作業してコミット
```bash
git add .
git commit -m "UIを新しく実装"
```

3. リモートにプッシュ
```bash
git push -u origin feature/new-ui
```

個人的によく使うコマンド一覧

a. ブランチを切らずに作業をしてしまった時、現在の変更を新しいブランチに退避するコマンド.   
case1 : まだadd / commitしてない時
```bash
git checkout -b 新しいブランチ名
```
-> そのまま新しいブランチに持っていけばok

case2 :  間違えて現在のブランチにコミットしてしまった時
```bash
git checkout -b 新しいブランチ名

# 間違って入れたコミットを取り消す (HEAD~nでn回前のcommtiを消せる)
git reset --hard HEAD~1
```

自戒: こまめにcommtiする

## 9/8
hyamamot/input.cのレビュー   
khanadat_protoの追加。   
このディレクトリでプロトタイプの作成を試みる。   

## 9/8
funcディレクトリで使えるコマンドの整理する。   
