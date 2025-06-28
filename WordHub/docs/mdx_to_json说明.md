### 杂项：mdx_to_json.py文件说明
**负责人**：[郑嘉祺](https://github.com/missswiftie)
#### 主要功能
- 互联网上的开源字典很多情况下以`.mdx`文件形式存在，为了获取其中的所有数据，需要将`.mdx`文件转化成格式清晰的文件，如`.json`文件。
- `mdx_to_json.py`文件实现了这一功能。
#### 实现步骤
- 应用`pyglossary`库，在虚拟环境中将`.mdx`文件转化成html形式的`.json`文件，以windows系统为例。
```bash
cd Your Project
python -m venv glossary-env
glossary-env\Scripts\activate
pip install pyglossary
pyglossary --write-format=JSON oxford_9.mdx oxford_9.json
```
- 通过`mdx_to_json.py`文件将`oxford_9.json`文件转化成结构清晰的`structed_oxford_9.json`文件，其中每个单词以如下形式存在：
```json
    "energize": {
    "word": "energize",
    "phonetics": {
        "uk": {
        "text": "ˈenədʒaɪz",
        "audio": "snd://energize__gb_1.spx"
        },
        "us": {
        "text": "ˈenərdʒaɪz",
        "audio": "snd://energize__us_1.spx"
        }
    },
    "pos": "verb",
    "definition": {
        "english": "to make sb enthusiastic about sth 使充满热情",
        "chinese": ""
    },
    "examples": [
        {
        "english": "a refreshing and energizing fruit drink 提神并增加能量的果汁饮料",
        "chinese": "提神并增加能量的果汁饮料",
        "audio": {
            "uk": "",
            "us": ""
        }
        }
    ]
    },
```
#### 代码解析
- `parse_word_entry`函数将一个单词的html文件内容转化成结构化的数据类型。其中参数`html_content`为字符串，返回值`result`为字典，数据结构如下所示。其中html内容用`beautifulSoup`解析。
```python
    result = {
        "word": "",
        "phonetics": {"uk": {}, "us": {}},
        "pos": "",
        "definition": "",
        "examples": []
    }
```
- `convert_to_structured_json`函数的输入参数为`input_file`以及`output_file`，将`input_file`中的html内容转化成结构化的数据结构，并以`.json`的格式写入`output_file`。