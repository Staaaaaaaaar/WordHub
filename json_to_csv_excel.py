import json
import pandas as pd
import re

#正则表达式分隔单词意思中的中英文
def split_definition(combined_str):
    """
    输入示例: "connected with the stars or outer space 星（的）；天体（的）；外层空间（的）；宇宙空间（的）"
    输出结果: ('connected with the stars or outer space', '星（的）；天体（的）；外层空间（的）；宇宙空间（的）')
    """
    # 匹配首个中文字符出现的位置（兼容全角括号）
    pattern = re.compile(r'^(.*?)([\u4e00-\u9fff（].*)$', re.UNICODE)
    
    if match := pattern.match(combined_str):
        english = match.group(1).strip()
        chinese = match.group(2).strip()
    else:
        english = combined_str.strip()
        chinese = ""
    
    # 处理英文部分末尾可能残留的标点
    english = re.sub(r'[\s・]+$', '', english)
    return english, chinese

# 读取JSON文件
with open('C:\\Users\\郑嘉祺\\vocabulary_learning\\oxford_9_folder\\oxford_9_test.json', 'r', encoding='utf-8') as f:
    data = json.load(f)

# 第一步：确定最大例句数量
max_examples = 0
max_key=""
for word_key in data:
    if examples := data[word_key].get("examples"):
        if len(examples)>max_examples:
            max_examples=len(examples)
            max_key=word_key

# 第二步：动态生成列头
columns = [
    "单词", "词性", "英文定义", "中文定义",
    "UK音标", "US音标"
]

# 添加动态例句列
example_columns = [f"例句{i+1}" for i in range(max_examples)]
columns += example_columns

rows = []

# 第三步：处理每个单词
for word_key in data:
    if not word_key:
        continue
    
    entry = data[word_key]
    print(f"Processing word: {word_key}")
    
    # 处理定义字段
    definition = entry.get("definition", {})
    if isinstance(definition, dict):
        english_meaning,chinese_meaning=split_definition(dict(definition).get("english",""))
    else:
        continue
    
    # 基础信息
    row_data = {
        "单词": entry.get("word", ""),
        "词性": entry.get("pos", ""),
        "英文定义": english_meaning,
        "中文定义": chinese_meaning,
        "UK音标": entry.get("phonetics", {}).get("uk", {}).get("text", ""),
        "US音标": entry.get("phonetics", {}).get("us", {}).get("text", "")
    }
    
    # 处理例句
    examples = [ex.get("english", "").strip() for ex in entry.get("examples", [])]
    for i in range(max_examples):
        row_data[f"例句{i+1}"] = examples[i] if i < len(examples) else ""
    
    rows.append(row_data)

# 创建DataFrame
df = pd.DataFrame(rows, columns=columns)

# 保存文件
df.to_csv("C:\\Users\\郑嘉祺\\vocabulary_learning\\oxford_9_folder\\oxford_9_test_csv.csv", 
          index=False, 
          encoding='utf-8-sig')

print(f"转换完成！共处理 {len(rows)} 个单词，最大例句数 {max_examples}")
print(f"Max example word:{max_key},examples:{max_examples}")
