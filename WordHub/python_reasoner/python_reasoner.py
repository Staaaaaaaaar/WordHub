from openai import OpenAI
import sys
import json
import argparse
import re
import sqlite3
import random
import os

def get_database(database):
    # 获取脚本所在目录的上一级目录(可执行文件目录)
    exe_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    
    if database=="1":
        # 指向可执行文件目录下的datas文件夹
        return os.path.join(exe_dir, "datas", "CET_4+6.db")
    # 可以根据需要添加其他数据库选项

def get_word(database):
    conn=sqlite3.connect(get_database(database))
    cursor=conn.cursor()

    cursor.execute("SELECT word FROM words")
    all_records=cursor.fetchall()
    random_record=random.choice(all_records) if all_records else None
    conn.close()
    return random_record[0] if random_record else "word"

database=""
word=""

def unicode_unescape(s):
    return re.sub(r'\\u([0-9a-fA-F]{4})', lambda m: chr(int(m.group(1), 16)), s)

def get_word_and_description():
    global word
    API_KEY="sk-e0ff2f28b0d744e2abb47d989311c436"
    model_name="deepseek-chat"
    client=OpenAI(api_key=API_KEY,base_url="https://api.deepseek.com")
    word_prompt=f"""
    请用英文对这个单词进行一个20词-30词左右的描述,描述中不能出现这个词本身：
    {word}
    """
    all_response=client.chat.completions.create(
        model=model_name,
        messages=[
            {
                "role":"system",
                "content":word_prompt            
            }
        ],
        stream=False,
        temperature=0.0
    )
    return all_response.choices[0].message.content

def get_translation(description):
    translation_prompt=f"""
    请翻译{description}为中文。
    """
    API_KEY="sk-e0ff2f28b0d744e2abb47d989311c436"
    model_name="deepseek-chat"
    client=OpenAI(api_key=API_KEY,base_url="https://api.deepseek.com")
    all_response=client.chat.completions.create(
        model=model_name,
        messages=[
            {
                "role":"system",
                "content":translation_prompt            
            }
        ],
        stream=False,
        temperature=0.0
    )
    return all_response.choices[0].message.content

def main():
    global word
    description=get_word_and_description()
    translation=get_translation(description)
    return {
        "status":"success",
        "word":word,
        "description":description,
        "translation":translation.strip()
    }

if __name__=="__main__":
    parser=argparse.ArgumentParser(description="单词处理工具")
    parser.add_argument("--database",type=str, required=True, help="数据库ID (1,2,3,4,5,6,7)")
    args=parser.parse_args()
    database=args.database
    word=get_word(database)
    try:
        result=main()
        print(json.dumps(result))
    except Exception as e:
        error_result = {
            "status": "error",
            "message": str(e),
            "database": args.database,
        }
        print(json.dumps(error_result))
        sys.exit(1)