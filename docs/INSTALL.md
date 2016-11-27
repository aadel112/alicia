
## Installation
Download Alicia from git

Install cpanm
```
curl -L https://cpanmin.us | perl - --sudo App::cpanminus
```

Then install the dependencies

```
cpanm --installdeps .
```

Add the Alicia directory to your path eg:

```
d=`pwd`
export ALICIA_DIR=$d
export PATH="$PATH:$d"
```

These last two need to be in a startup file like ~/.bashrc

