from flask_wtf import FlaskForm
from wtforms import StringField, SubmitField
from wtforms.validators import DataRequired, Length, Email, URL, ValidationError
from app.models import Department


class StudentForm(FlaskForm):
    name = StringField('Name',
                           validators=[DataRequired(), Length(min=2, max=20)])
    email = StringField('Email',
                        validators=[DataRequired(), Email()])
    department = StringField('Department',
                        validators=[DataRequired()])
    submit = SubmitField('Submit')


class DepartmentForm(FlaskForm):
    url = StringField('URL',
                      validators=[DataRequired(), URL()])
    name = StringField('name',
                       validators=[DataRequired(), Length(min=2, max=100)])
    submit = SubmitField('Submit')

    def validate_department(self, username):
        dep = Department.query.filter_by(username=username.data).first()
        if dep:
            raise ValidationError('That department already exists. Please choose a different one.')
