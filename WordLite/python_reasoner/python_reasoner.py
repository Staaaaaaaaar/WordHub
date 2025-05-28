from openai import OpenAI
from get_word import get_word
import sys
import json
import argparse

dificultty=""
database=""
word=""

word_prompt=f"""
请用英文对这个单词进行一个20词-30词左右的描述，描述难度为{dificultty},描述中不能出现这个词本身：
{word}
"""
description=""
translation_prompt=f"""
请翻译{description}为中文，并解释每个单词的释义。
"""

def get_word_and_description():
    global word,description
    API_KEY="sk-e0ff2f28b0d744e2abb47d989311c436"
    model_name="deepseek-chat"
    client=OpenAI(api_key=API_KEY,base_url="https://api.deepseek.com")
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
    description=all_response.choices[0].message.content
    return all_response.choices[0].message.content

def get_translation():
    API_KEY="sk-e0ff2f28b0d744e2abb47d989311c436"
    model_name="deepseek-chat"
    client=OpenAI(api_key=API_KEY,base_url="https://api.deepseek.com")
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

def main():
    global word,description
    translation=get_translation()
    return {
        "status":"success",
        "word":word,
        "description":description,
        "translation":translation
    }

if __name__=="__main__":
    parser=argparse.ArgumentParser(description="单词处理工具")
    parser.add_argument("--database", type=int, required=True, help="数据库ID (1,2,3,4,5,6,7)")
    parser.add_argument("--difficulty", type=str, required=True, help="难度级别 (简单, 中等, 困难)")
    args=parser.parse_args()
    database=args.database
    word=get_word(database)
    dificulty=args.dificulty
    try:
        result=main()
        print(json.dumps(result))
    except Exception as e:
        error_result = {
            "status": "error",
            "message": str(e),
            "database": args.database,
            "difficulty": args.difficulty
        }
        print(json.dumps(error_result))
        sys.exit(1)