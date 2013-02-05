pkill -f firefox
pkill -f chrome

bleacgbit --delete firefox.*
bleachbit --delete google_chrome.*

sudo /etc/init.d/dns-clean start

read -p "Press [Enter] key to exit script..."
