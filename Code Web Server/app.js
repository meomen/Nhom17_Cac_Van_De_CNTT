const express   = require('express')
const app       = express()
const config    = require('config')
const path      = require('path')
const bodyParse = require('body-parser')
const cors      = require('cors')
const models    = require('./server/models')

app.use(cors())
app.use(bodyParse.json())
app.use(bodyParse.urlencoded({ extended: true }))



app.get('/metrics', (req, res) => {
    console.log(req.query)
    models.Data.findAll()
    .then(data => {
        res.json(data)
    })
})
app.post("/metrics", (req, res) => {
    let data = req.body.data;
    models.Data.create({
        t1: data.split('|')[0],
        t2: data.split('|')[1]
    })
    .then(_res => { 
        res.json(_res)
    })
    .catch(err => {
        console.log(err)
    })
})

app.listen(config.application.port, () => {
    console.log("Listen . . . " + config.application.port)
})