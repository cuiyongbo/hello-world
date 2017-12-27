#!/usr/bin/sh

# Credit http://stackoverflow.com/a/2514279

for branch in `git branch -r | grep -v HEAD`
do
	echo -e `git show --format="%ai %ar by %an" $branch | head -n 1` \\t$branch
done |
	sort -r


#for branch in `git branch -r | grep -v HEAD`
#do
#	echo -e `git show --pretty=format:"%Cred %cn %Cgreen %ar %Creset" $branch | head -n 1` $branch
#done | 
#	sort -r

