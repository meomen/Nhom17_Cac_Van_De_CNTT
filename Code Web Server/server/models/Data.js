module.exports = (sequelize, DataTypes) => {
    return sequelize.define('data', {
        id: {
            type: DataTypes.INTEGER,
            autoIncrement: true,
            primaryKey: true
        },
        t1: {
            type: DataTypes.STRING,
            allowNull: false,
            defaultValue: ''
        },
        t2: {
            type: DataTypes.STRING,
            allowNull: false,
            defaultValue: ''
        }
    });
};
module.exports.name = 'Data'