#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

PS1='\u \e[0;92min\e[0m \e[1;34m\W\e[0m \$ '

export CHROME_EXECUTABLE=/usr/bin/chromium #for flutter web development
alias ls='ls --color=auto'

function p {
	clear && ffplay -hide_banner -loop 0 "$(find ~/dati/music/* | sort | fzf)"
}

#thanks to @mircodezorzi
function pa {
    if [ $# -eq 0 ]; then
        yay -S --noconfirm $(cat "$HOME/.cache/yay/completion.cache" \
            | awk '{print $1}' | fzf --multi --preview 'yay -Si {} | grep " : "')
    else
        yay -S --noconfirm $@
    fi
}

function pr {
    if [ $# -eq 0 ]; then
        sudo pacman -Rns --noconfirm $(pacman -Qq | fzf --multi --preview 'yay -Qi {} | grep " : "')
    else
        sudo pacman -Rns --noconfirm $@
    fi
}

