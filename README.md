# com_cli

## Usage


### 1. read_value

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




### 1. read_keyword

```c++
using namespace std;
vector<string> table = {"apple", "banana", "chocolate"};
int ianswer = 0;//= apple
com_cli::read_keyword("What your favourite food ?", table, &ianswer);

```

Then, 

```bash
	What your favourite food ?
	  
	apple banana chocolate
	  
	Select   1 Option
  $CLI> 
```

If you type `banana` and then press the Enter key, `ianswer` is modified to 1.
Of cource, when you just press the Enter key, `ianswer` is 0.
In `read_keyword` sessions, users of app can use tab-completion, which candidates are strings in the `table`.

#### for multiple keyword


```c++
using namespace std;
vector<string> table = {"apple", "banana", "chocolate", "durian", "eel"};
vector<int> answer;
int nreply = -1;
com_cli::read_keyword("What food do you want ?", table, nreply, &answer);
```

Then,

```bash
	What food do you want ?

	apple banana chocolate durian eel 

	CLI:  Select   1 or More, Then OK
  $CLI> 
```

If you require **exact** `nreply` answer, `nreply` should be **positive**.

## Installation

`git clone https://github.com/goroyabu/com_cli`

First, `make`

Then, `make install`

Now, write `source /path/to/here/this.sh` on ~/.bash_profile


## Documentation

First, `cd documentation/`

Then, `make`

And, `open toppage.html`

Please read documentation/README.