"llamado para usar plugins desde github repository creo
call plug#begin("~/.config/plugged")
  " Plugin Section
  Plug 'dracula/vim'
call plug#end()

"Config Section

set title  " Muestra el nombre del archivo en la ventana de la terminal
set relativenumber  " Muestra los números relativos de las líneas
set mouse=a  " Permite la integración del mouse (seleccionar texto, mover el cursor)

set nowrap  " No dividir la línea si es muy larga

set cursorline  " Resalta la línea actual
set colorcolumn=120  " Muestra la columna límite a 120 caracteres

" Indentación a 2 espacios
set tabstop=2
set shiftwidth=2
set softtabstop=2
set shiftround
set expandtab  " Insertar espacios en lugar de <Tab>s

set hidden  " Permitir cambiar de buffers sin tener que guardarlos

set ignorecase  " Ignorar mayúsculas al hacer una búsqueda
set smartcase  " No ignorar mayúsculas si la palabra a buscar contiene mayúsculas

set spelllang=en,es  " Corregir palabras usando diccionarios en inglés y español

set termguicolors  " Activa true colors en la terminal
set background=dark  " Fondo del tema: light o dark
colorscheme zellner  " Nombre del tema

if(has("termguicolors"))
  set termguicolors
endif
syntax enable
colorscheme dracula
