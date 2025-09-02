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