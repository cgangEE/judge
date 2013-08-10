set mouse=a
set nu
set history=4000
set backspace=2
set shiftwidth=4
set tabstop=4
set cindent
syntax on

func! R()
	exec ":w"
	exec "!clear&&g++ -I /usr/include/mysql %<.cpp -o %< -L /usr/lib/mysql -lmysqlclient"
	exec "!./%<"
endfunc

func! F()
	exec ":w"
	exec "!clear&&g++ %<.cpp -o %<"
	exec "!./%<"
endfunc

:nmap<silent> <C-a> ggvG$"+y
:nmap<silent> <C-v "+p
:map<F9> :call R()<CR>
:map<F8> :call F()<CR>
