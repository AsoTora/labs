from flask import render_template, url_for, flash, redirect
from app import app, db
from app.models import Department, Student
from app.forms import StudentForm, DepartmentForm


@app.route("/")
@app.route("/home")
def home():
    departments = Department.query.all()
    return render_template('home.html', Department=departments, title="Lab5_shvedau", departments=departments)


@app.route("/new_student", methods=['GET', 'POST'])
def new_student():
    form = StudentForm()
    if form.validate_on_submit():
        stud = Student(name=form.name.data,
                       email=form.email.data, department_id=Department)
        db.session.add(stud)
        db.session.commit()
        flash('Your stud has been created!', 'success')
        return redirect(url_for('home'))
    return render_template('create_student.html', title='New Student',
                           form=form)


@app.route("/new_dep", methods=['GET', 'POST'])
def new_dep():
    form = StudentForm()
    if form.validate_on_submit():
        stud = Student(name=form.name.data,
                       email=form.email.data, department_id=1)
        db.session.add(stud)
        db.session.commit()
        flash('Your stud has been created!', 'success')
        return redirect(url_for('home'))
    return render_template('create_student.html', title='New Student',
                           form=form)