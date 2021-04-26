const path = require("path");
const HtmlWebpackPlugin = require("html-webpack-plugin");
const CompressionPlugin = require("compression-webpack-plugin");

module.exports = {
		module: {
				rules: [
						{
								test: /\.css$/i,
								use: ['style-loader', 'css-loader', 'postcss-loader']
						},
						{
								test: /\.jsx$/,
								exclude: /node_modules/,
								use: ["babel-loader"]
						},
						{
								test: /\.js$/,
								exclude: /node_modules/,
								use: ["babel-loader"]
						}
				]
		},
		optimization: {
				// splitChunks: { chunks: "all" },
				minimize: true
		},
		entry: {
				index: path.resolve(__dirname, "src", "main.jsx")
		},
		output: {
				path: path.resolve(__dirname, "build"),
				publicPath: '/'
		},
		devServer: {
				historyApiFallback: true,
		},
		plugins: [
				new CompressionPlugin({
						test: /\.(js|jsx|css|svg)$/
				}),
				new HtmlWebpackPlugin({
						template: path.resolve(__dirname, "index.html")
				})
		],
		resolve: {
				extensions: ['', '.js', '.jsx'],
		}
};
