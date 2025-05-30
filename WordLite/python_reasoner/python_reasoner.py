from openai import OpenAI
from get_word import get_word
import sys
import json
import argparse
import re

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