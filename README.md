# com_cli

## Overview

com_cli は コマンドラインによる対話型インターフェースを提供する C++ 用ライブラリです。
以下は com_cli の特長です。仕様の詳細は Documentation をご覧ください。( Python 用ラッパー関数もそのうち書くかも。)

### 1. コマンドラインインターフェース用の関数群

com_cli の関数を使って標準入力からの変数の読み込みを簡単に行えます。

例えば、

```c++
int n = 100;
com_cli::read_value<int>("number of event", &n); 
```

とすると、

```shell-session
	$ number of event : 100 ?  
```

となり、ここで入力した値が、変数`n`に格納されます。

- 入力時は、GNU Readline のタブ補完とヒストリー機能を利用できます。
- 特にカスタムタブ補完をとても簡単に設定することが可能です。
- CLintrd, CLkeyrd 等、過去の関数との互換性を持ちます。

### 2. スクリプト読み込みとコマンドの実行

com_cli を使ったプログラムを利用するユーザーは、入力内容を記述したスクリプト(.com)を読み込ませることで同じ内容を何度も入力する手間を省くことができます。

```
    CLI> @my_process.com
```



## Installation

### Requirements
com_cliの依存関係は以下の通りです。
Mac OS X El Capitan, High Sierra, Mojaveでは動作確認しています。
Linuxは駄目かも。

- gcc 4.2.1
- GNU Make 3.81
- GNU Readline 7.0.5

Readlineはhomebrewで入れられます。
PythonやROOTで要求されるので、それらが入っていれば、既にあるかと思います。

```
brew install readline
```


### Installation & Setup
インストールは任意のディレクトリ下($HOME/soft/等)で、以下の通りに行ってください。

```
git clone https://github.com/goroyabu/com_cli
cd com_cli/
make install
```

~/.bash_profile 等の任意の設定ファイルに以下を参考に記載してください。

```
source $HOME/soft/com_cli/this.sh
```
 
If you want to uninstall, `make uninstall`

## Usage

よく使う関数の使い方を以下に示します。

| 主な関数 | 処理内容 |
| :-- | :-- |
| `read_value<T>` | T型を標準入力から読み取る関数. Require to type a value. | 
| `read_keyword<T>` | 選択肢を表示して、その中から選ばせる関数. Require to select options in a table. | 
| `init` / `end` | Called the beginning/end of a process. |

- オプション設定用の関数の詳細は Documentation をご覧ください。

### 1. read_value

`read_value` is a function template to require a new value.

```c++
int n = 100;
com_cli::read_value<int>("number of event", &n); 
```

Then,

```shell-session
	$ number of event : 100 ?  
```

If you just press the Enter key, `n` remains 100.

#### for multiple value

#### yes or no


### 2. read_keyword

複数の選択肢の中から、任意の個数を選んで、入力させる関数です。

例えば、

```c++
std::vector<std::string> table = {"apple", "banana", "chocolate"};
int ianswer = 0;//= apple
com_cli::read_keyword("What your favourite food ?", table, &ianswer);

```

とすると、 

```
	What your favourite food ?
	  
	apple banana chocolate
	  
	CLI: Select   1 Option
  $CLI> 
```

ここで、`banana`と入力し、エンターを押すと、`ianswer`の値は`banana`に対応する`1`に変更されます。もちろん、何も入力せずにエンターを押したなら、`ianswer`は`0`のままです。`read_keyword`の入力中は選択肢のタブ補完が可能なので、この場合、`b`を入力して、タブを押すだけで`banana`と補完されます。

If you type `banana` and then press the Enter key, `ianswer` is modified to 1.
Of cource, when you just press the Enter key, `ianswer` is 0.
In `read_keyword` sessions, users of app can use tab-completion, which candidates are strings in the `table`.

#### for multiple keyword

ユーザーに複数の回答を入力させることもできます。
例えば、

```c++
std::vector<std::string> table = {"apple", "banana", "chocolate", "durian", "eel"};
std::vector<int> answer;
int nreply = -1;
com_cli::read_keyword("What food do you want ?", table, nreply, &answer);
```

とすると、

```
	What food do you want ?

	apple banana chocolate durian eel 

	CLI:  Select   1 or More, Then OK
  $CLI> 
```
| nreply | 要求する回答数 |
| :--: | :--: |
| <0 (negative) | `nreply` or more |
| >0 (positive) | exact `nreply`   |


### 3. init / end

ヒストリー機能を利用する場合に呼ぶ必要のある、設定用の関数です。

```c++
//beginning of myapp
com_cli::init("myapp", "~/.myapp_history");

//some process

//end of myapp
com_cli::end();
```

Call `init()` before you use com_cli functions.
Otherwise, the default prompt and the default history file are used.
("CLI" and ".cli_hist")

Call `end()` after you used com_cli functions.
Otherwise, command typed in `myapp` are not saved in the history file.


### 4. Read a command file


### 5. Tab-completion and history





## Documentation

詳細なドキュメントをDoxygenで生成できます。

### Requirements
homebrewなどを通して、以下をインストールしてください。

 - graphviz
 - doxygen

### Generations of Docs

com_cliをインストールしたディレクトリ($HOME/soft/com_cli/等)に移動して、

```
cd documentation/
make
```

生成したドキュメントを見るには、`toppage.html`をウェブブラウザでご覧ください。
 
```
open toppage.html
```

Please read [documentation/README](documentation/README.md)

## Licence


## Authors
Goro Yabu 

## References
