pkgdata_DATA=ru/LC_MESSAGES/guess.mo

messages.pot: guess.pot ../src/guess.c
	xgettext -k_ -c ../src/guess.c -o messages.new.pot
	cp guess.pot messages.pot
	msgmerge -U messages.pot messages.new.pot

ru.po:	messages.pot
	msgmerge -U $@ $<

ru/LC_MESSAGES/guess.mo: ru.po
	mkdir -p `dirname $@`
	msgfmt $< -o $@

clean-local:
	-rm -rf autom4te.cache .deps
