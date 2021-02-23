from app import app, db

if __name__ == '__main__':
    # clear and populate
    with app.app_context():
        db.drop_all()
        db.create_all()
        db.engine.execute('''INSERT INTO department VALUES (1, 'фиту', 'www.fitu.com')''')
        db.engine.execute('''INSERT INTO department VALUES (2, 'фик', 'www.fik.com');''')
        db.engine.execute('''INSERT INTO department VALUES (3, 'ksis', 'www.ksis.com');''')
        db.engine.execute('''INSERT INTO student VALUES (1, 'andrei', 'andrei@gmail.com', 1);''')
        db.engine.execute('''INSERT INTO student VALUES (2, 'masha', 'masha@gmail.com', 3);''')
        db.engine.execute('''INSERT INTO student VALUES (3, 'ogoto', 'ogoto@gmail.com', 1);''')
    app.run(debug=True)