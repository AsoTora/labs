from app import db

class Student(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(20), unique=True, nullable=False)
    email = db.Column(db.String(120), unique=True, nullable=False)

    department_id = db.Column(db.Integer, db.ForeignKey('department.id'), nullable=False)
    # department = db.relationship('Department')

    def __repr__(self):
        return f"User('{self.name}', '{self.email}')"


class Department(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(100), nullable=False)
    URL = db.Column(db.String(100))
    students = db.relationship('Student', backref='department', lazy=True)

    def __repr__(self):
        return f"Department('{self.name}', '{self.site}')"