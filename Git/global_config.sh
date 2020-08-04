#!/bin/bash

# ./global_config.sh AmalLight ilovenewblood@gmail.com

pass=`combo mohammad`

echo $pass | sudo -S rm -f /usr/bin/git_global
echo $pass | sudo -S ln -s /home/kaumi/Git/global_config.sh /usr/bin/git_global

if (( ${#@} == 2 ));

then
    git config --global user.name  $1
    git config --global user.email $2

else
    echo ''
    echo "1:name ; 2:email"
    echo
fi

echo

git config --global core.editor "notepad -multiInst -nosession"

# sudo apt install meld -y

git config --global diff.tool  meld
git config --global merge.tool meld

git config --global difftool.meld.path  /usr/bin/meld
git config --global mergetool.meld.path /usr/bin/meld

git config --global difftool.prompt  false
git config --global mergetool.prompt false

git config --global alias.hist 'log --oneline --graph --decorate --all'

git config --global push.default simple

git config --global --list

echo
