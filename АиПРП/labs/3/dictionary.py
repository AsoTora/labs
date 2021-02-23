# app
from flask import *

##############
# configurations
##############

database = 'test_db'
tablename = 'dictionary'
mysqluser = 'root'
password = 'password'
ip = 'localhost'

app = Flask(__name__, instance_relative_config=True )
app.config['SECRET_KEY'] = 'f3cfe9ed8fae309f02079dbf'
app.config['SQLALCHEMY_DATABASE_URI'] =  f'mysql+pymysql://{mysqluser}:{password}@{ip}/{database}'


##############
# db
##############
from flask_sqlalchemy import SQLAlchemy
db = SQLAlchemy(app)

class Dictionary(db.Model):
    id = db.Column(db.Integer, unique=True, primary_key=True, )
    word = db.Column(db.String(100), unique=True)
    translation = db.Column(db.String(100), unique=True)

    def __init__(self, word=None, translation=None):
        self.word = word
        self.translation = translation

    def __repr__(self):
        return f'{self.translation}'


##############
# forms
##############
from wtforms.validators import DataRequired
from wtforms import StringField, SubmitField
from flask_wtf import FlaskForm

class input_form(FlaskForm):
    word = StringField('Enter a word', validators=[DataRequired()])
    submit = SubmitField('Submit')

class new_word(FlaskForm):
    word = StringField('Enter a word', validators=[DataRequired()])
    translation = StringField('Enter a translation', validators=[DataRequired()])
    submit = SubmitField('Submit')


##############
# routes
##############

@app.route('/', methods=['GET', 'POST'])
def dictionary():
    session.permanent = True
    form = input_form()
    
    if request.method == 'GET':
        return render_template("submit_output.html", form=form)

    if request.method == 'POST' and form.validate_on_submit():
        input_word = form.word.data.lower()
        found_translation = Dictionary.query.filter_by(word=input_word).first()
        
        if Dictionary.query.filter_by(word=input_word).first() is None:
            return redirect(url_for("suggest"))
        
        return render_template("submit_output.html", output=found_translation, form=form)


@app.route('/suggest', methods=['GET', 'POST'])
def suggest():
    form = new_word()
    if request.method == 'GET':
        return render_template("radio_button.html", form=form)

    if request.method == 'POST':
        word = form.word.data.lower()
        transl = form.translation.data.lower()
        input_word = Dictionary(word=word, translation=transl)

        # debug
        print("***"*10)
        print(input_word)
        print("***"*10)

        if Dictionary.query.filter_by(word=word, translation=transl).first() is None:
            db.session.add(input_word)
            db.session.commit()
            return redirect(url_for("dictionary"))
        else:
            return "already exists"

if __name__ == '__main__':
    db.drop_all()
    db.create_all()
    app.run(debug=True)
