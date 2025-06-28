import json
from bs4 import BeautifulSoup
import os

def parse_word_entry(html_content):
    """解析单个单词的HTML内容"""
    soup = BeautifulSoup(html_content, 'html.parser')
    
    # 基础结构
    result = {
        "word": "",
        "phonetics": {"uk": {}, "us": {}},
        "pos": "",
        "definition": "",
        "examples": []
    }

    # 解析单词主体
    main_word = soup.find('h', {'e_id': True})
    if main_word:
        result["word"] = main_word.get_text(strip=True).replace('·', '')

    # 解析音标
    phon_blocks = soup.find_all('phon-blk')
    for i, block in enumerate(phon_blocks[:2]):
        dialect = "uk" if i == 0 else "us"
        result["phonetics"][dialect]["text"] = block.get_text(strip=True).replace('/', '')
        
        # 获取对应音频
        audio_tag = block.find_parent('pron-g').find_next('a', href=True)
        if audio_tag:
            result["phonetics"][dialect]["audio"] = audio_tag['href']

    # 解析词性
    pos_tag = soup.find('pos')
    if pos_tag:
        result["pos"] = pos_tag.get_text(strip=True)

    # 解析定义
    def_tag = soup.find('def')
    if def_tag:
        chinese = def_tag.find('chn', {'fthzmark': True})
        english = def_tag.get_text(' ', strip=True).split('chnsep')[0].strip()
        result["definition"] = {
            "english": english,
            "chinese": chinese.get_text(strip=True) if chinese else ""
        }

    # 解析例句
    for example in soup.find_all('x', {'e_id': True}):
        eng_text = example.get_text(' ', strip=True).split('chn')[0].strip()
        chn_text = example.find('chn').get_text(strip=True) if example.find('chn') else ""
        
        # 获取例句音频
        audio_links = {
            "uk": "",
            "us": ""
        }
        for audio in example.find_all('a', href=True):
            href = audio['href']
            if '_gbs_' in href:
                audio_links["uk"] = href
            elif '_uss_' in href:
                audio_links["us"] = href

        result["examples"].append({
            "english": eng_text,
            "chinese": chn_text,
            "audio": audio_links
        })

    return result

def convert_to_structured_json(input_file, output_file):
    """转换主函数"""
    # 读取原始JSON文件
    with open(input_file, 'r', encoding='utf-8') as f:
        raw_data = json.load(f)
    
    structured_data = {}
    
    # 处理每个词条
    for key, html in raw_data.items():
        # 处理多词性格式（如 "word|words"）
        print(key)
        base_word = key.split('|')[0]
        entry = parse_word_entry(html)
        structured_data[base_word] = entry

    # 保存结构化JSON
    with open(output_file, 'w', encoding='utf-8') as f:
        json.dump(structured_data, f, ensure_ascii=False, indent=2)

# 使用示例
print("脚本绝对路径:", os.path.abspath(__file__))
convert_to_structured_json('C:\\Users\\郑嘉祺\\vocabulary_learning\\oxford_9\\oxford_9.json', 'structured_dictionary.json')