import sqlite3
import random
from get_database import get_database

def get_word(database):
    conn=sqlite3.connect(get_database(database))
    cursor=conn.cursor()

    cursor.execute("SELECT word FROM words")
    all_records=cursor.fetchall()
    random_record=random.choice(all_records) if all_records else None
    conn.close()
    return random_record[0] if random_record else "word"