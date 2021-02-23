import sqlalchemy
from sqlalchemy import MetaData, Table, Integer, String, Column, text
metadata = sqlalchemy.MetaData()

database = 'test_db' 
tablename = 'dictionary' 
mysqluser = 'root'
password = 'password'
ip = 'localhost'

table = Table(
    tablename, metadata,
    Column('id', Integer, primary_key=True),
    Column('word', String(length=100)),
    Column('translation', String(length=100))
)


def init_db():
    engine = sqlalchemy.create_engine(
        f'mysql+pymysql://{mysqluser}:{password}@{ip}/{database}', echo=True)

    # clear 
    with engine.connect() as conn:
        for table in reversed(metadata.sorted_tables):
            conn.execute(table.delete())

    # create
    metadata.create_all(engine)

    with engine.connect() as conn:
        # change charset for russian words
        conn.execute(text("SET collation_connection = 'utf8_general_ci'"))
        conn.execute(
            text(f"ALTER DATABASE {database} CHARACTER SET utf8 COLLATE utf8_general_ci;"))
        conn.execute(text(
            f"ALTER TABLE {tablename} CONVERT TO CHARACTER SET utf8 COLLATE utf8_general_ci;"))
