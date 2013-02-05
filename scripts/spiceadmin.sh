echo "Type the email of the user you would like to make a 
Spice Admin, followed by [ENTER]:"

read user

cd /var/www/sites/spiceworks/frontend

sudo -u capistrano JRUBY_OPTS=--1.9 RAILS_ENV=verification bundle exec script/spicecli/make_admin -e  $user

read -p "Press [Enter] key to exit script..."



