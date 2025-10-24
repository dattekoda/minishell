#!/bin/bash

# ./bonus ディレクトリ配下の「ファイル」(-type f) を検索
# ただし、.DS_Store や .git などのドットファイル（隠しファイル）は除外する (-name "[!.]*.*")
find ./bonus -type f -name "[!.]*.*" | while read -r file; do
    
    # ファイルパスからディレクトリ名とファイル名を取得
    dirname=$(dirname "$file")
    filename=$(basename "$file")
    
    # 拡張子とベース名（拡張子を除いた部分）に分離
    extension="${filename##*.}"
    base="${filename%.*}"
    
    # 新しいファイル名を構築
    new_name="${base}_bonus.${extension}"
    
    # 実行結果をまず表示（ドライラン）
    # echo mv "$file" "${dirname}/${new_name}"
    
    # 期待通りの動作をすることを確認したら、上の 'echo' を消して下の行を実行する
    mv "$file" "${dirname}/${new_name}"
    
done