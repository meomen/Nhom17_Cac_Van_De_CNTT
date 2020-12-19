const path = require('path')
const Sequelize = require('sequelize')
const database = require('config').database

const sequelize = new Sequelize(database.dbName, database.dbUser, database.dbPassword, {
    define: {
        freezeTableName: true
    },
    host: database.dbHost || 'localhost',
    port: database.dbPort,
    logging: database.logging,
    dialect: database.dialect
})

sequelize.sync({
    force: false
})
.then(() => {
    console.log("SYNC DB SUCCESS")
})
.catch(err => {
    console.log("SYNC DB FAIL", err)
})

// let models = ['User', 'Image', 'Project', 'User', 'UserImage']
// models.forEach(model => {
//     module.exports[model] = require(path.join(__dirname, model))(sequelize, Sequelize.DataTypes)
// })

module.exports["Data"] = require('./Data')(sequelize, Sequelize.DataTypes)

module.exports.sequelize = sequelize