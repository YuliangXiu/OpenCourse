#!/bin/sh

git filter-branch --env-filter '

OLD_EMAIL="YuliangXiu@users.noreply.github.com"
OLD_EMAIL2="Personals@osamusakaisuketekiMacBook-Pro.local"
OLD_EMAIL3="XiuCode@users.noreply.github.com"
CORRECT_NAME="YuliangXiu"
CORRECT_EMAIL="yuliangxiu@gmail.com"

if [ "$GIT_COMMITTER_EMAIL" = "$OLD_EMAIL" -o "$OLD_EMAIL2" -o "$OLD_EMAIL3" ]
then
    export GIT_COMMITTER_NAME="$CORRECT_NAME"
    export GIT_COMMITTER_EMAIL="$CORRECT_EMAIL"
fi
if [ "$GIT_AUTHOR_EMAIL" = "$OLD_EMAIL" -o "$OLD_EMAIL2" -o "$OLD_EMAIL3" ]
then
    export GIT_AUTHOR_NAME="$CORRECT_NAME"
    export GIT_AUTHOR_EMAIL="$CORRECT_EMAIL"
fi
' --tag-name-filter cat -- --branches --tags
