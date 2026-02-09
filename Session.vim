let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/Documents/kody/bettergl
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +136 ~/Documents/kody/bettergl/src/main.cpp
badd +3 ~/Documents/kody/bettergl/src/bettergl/include/bettergl/Debugging.hpp
badd +39 ~/Documents/kody/bettergl/src/bettergl/include/bettergl/GLTypes.hpp
badd +7 ~/Documents/kody/bettergl/src/bettergl/include/bettergl/Program.hpp
badd +54 ~/Documents/kody/bettergl/src/bettergl/Program.cpp
badd +533 ~/Documents/kody/bettergl/glad/include/glad/glad.h
badd +1 ~/Documents/kody/bettergl/CMakeLists.txt
badd +6 ~/Documents/kody/bettergl/src/bettergl/CMakeLists.txt
argglobal
%argdel
edit ~/Documents/kody/bettergl/src/bettergl/Program.cpp
argglobal
balt ~/Documents/kody/bettergl/src/main.cpp
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal nofoldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 54 - ((42 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 54
normal! 040|
tabnext 1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
set hlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
