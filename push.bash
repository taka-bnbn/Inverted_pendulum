#!/bin/bash

# スクリプトの説明を表示
echo "Running Git commands: add, commit, and push."

# git add -A の実行
git add -A
echo "All changes have been added."

# コミットメッセージを入力
read -p "Enter your commit message: " commit_message
git commit -m "$commit_message"
echo "Changes committed with message: '$commit_message'"

# git push の実行
git push
echo "Changes have been pushed to the repository."

