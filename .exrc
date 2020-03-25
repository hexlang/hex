autocmd! BufRead,BufNewFile  *.h  set filetype=cpp
let g:syntastic_filetype_map = { "h": "c" }
let g:syntastic_cpp_checkers = ["gcc", "cppcheck"]

"AutoFormat
augroup autoformat_settings
	autocmd FileType c,cpp AutoFormatBuffer clang-format
augroup END

set tabstop=4
set softtabstop=4
set shiftwidth=4
set noexpandtab

set colorcolumn=110
highlight ColorColumn ctermbg=darkgray

let &path.="/usr/include"
set makeprg="make"
