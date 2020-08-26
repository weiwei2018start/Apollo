
# encoding:utf-8
from flask import Flask, jsonify, request
import json

app = Flask(__name__)
@app.route('/first_page', methods=['GET'])
def show_entries():
    page = request.args.get('page')
    pagesize = request.args.get('pagesize')
    category = request.args.get('category')
    handle = {"page":page, "pagesize":pagesize, "category":category}

    return jsonify(handle)

# username = request.form.get('username', '')
# password = request.form.get('password', '')
if __name__ == '__main__':
    print ("Hello world")
    # app.run()
    app.run(host="0.0.0.0", port = 5000, threaded = True)


