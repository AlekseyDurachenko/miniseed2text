# miniseed2text
Converting the miniseed file into the textual file

## Output textual format
```
NET|STA|CHAN|LOCATION|HPTIME|VALUE\n
```
where:
* NET - network name
* STA - station name
* CHAN - channel name
* LOCATION - location code
* HPTIME - microseconds since 1 jan 1970
* VALUE - int32, float or double value

## Usage
```bash
miniseed2text Ver 0.1.0 Converting the miniseed file into the textual file
Developer(s):
    2015 Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
Usage:
    miniseed2text input.mseed output.txt
Libraries:
    libmseed 2.13
```

where:
* input.mseed - input miniseed file
* output.txt - output textual file

## Compiling

### GNU/Linux
```bash
git clone https://github.com/AlekseyDurachenko/miniseed2text.git miniseed2txt
cd miniseed2txt
git submodule init
git submodule update
cd submodules/libmseed
make
cd ../..
make
```


