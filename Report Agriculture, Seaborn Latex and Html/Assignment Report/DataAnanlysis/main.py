import numpy as np
import pandas as pd
import seaborn as sns
from pandas.plotting import scatter_matrix
from sklearn.preprocessing import MinMaxScaler

# Update the file path accordingly
df = (pd.read_csv(r'C:\Users\adith\OneDrive\Desktop\Gituni\COMP170-1-2306514\Assigment Report\Crop_recommendation.csv'))
      #(r'C:\Users\adith\OneDrive\Desktop\Gituni\COMP170-1-2306514\Assigment Report\Crop_recommendation.csv'))
      #(r'D:\COMP170-1-2306514\Assigment Report\Crop_recommendation.csv'))
df1 = (pd.read_csv(r'C:\Users\adith\OneDrive\Desktop\Gituni\COMP170-1-2306514\Assigment Report\indiancrop_dataset.csv'))

# Display the first and last few rows of the dataframe
print(df.head())
print(df.tail())

# Descriptive statistics
print(df.describe())

# Extracting specific columns
selected_columns = ['N', 'P', 'K', 'temperature', 'humidity', 'ph', 'rainfall', 'label']
print(df[selected_columns])

# Filtering data based on conditions
print(df.loc[df['humidity'] > 80])
print(df.query('humidity < 60'))
print(df.loc[~df['ph'].isna()])

# Creating a new feature
df['humidity_to_temperature_ratio'] = df['humidity'] / df['temperature']

# Histogram
# df['N'].plot(kind='hist', bins=100, title='Distribution of Nitrogen Percentage', figsize=(15, 5))
# plt.show()

# Histogram
# df['K'].plot(kind='hist', bins=100, title='Distribution of Potassium Percentage', figsize=(15, 5))
# plt.show()

# Histogram
# df['P'].plot(kind='hist', bins=100, title='Distribution of Phursphorus Percentage', figsize=(15, 5))
# plt.show()

# Scatter plot
# df.plot(kind='scatter', x='N', y='humidity', title='Nitrogen percentage in soil Vs Humidity')
# plt.show()

# Scatter plot
# df.plot(kind='scatter', x='P', y='humidity', title='Phourphrus percentage in soil Vs Humidity')
# plt.show()

# Scatter plot
# df.plot(kind='scatter', x='K', y='humidity', title='Potassium percentage in soil Vs Humidity')
# plt.show()

# Save processed data to CSV
df.to_csv('processed_data.csv')

# Additional Analysis and Visualization (placeholders)

# Boxplot using Seaborn
sns.color_palette("viridis", as_cmap=True)
sns.boxplot(y='label', x='P', data=df[df['rainfall'] > 150], palette="viridis")
plt.show()

sns.color_palette("viridis", as_cmap=True)
sns.boxplot(y='label', x='N', data=df[df['rainfall'] > 150], palette="viridis")
plt.show()

sns.color_palette("viridis", as_cmap=True)
sns.boxplot(y='label', x='K', data=df[df['rainfall'] > 150], palette="viridis")
plt.show()

#box and wisker
sns.color_palette("viridis", as_cmap=True)
sns.boxplot(y='label',x='ph',data=df, palette="viridis")
plt.show()

sns.color_palette("viridis", as_cmap=True)
sns.scatterplot(x="humidity", y="temperature", data=df, palette="viridis")
plt.show()

sns.color_palette("viridis", as_cmap=True)
sns.scatterplot(x="humidity", y="ph", data=df, palette="viridis")
plt.show()

sns.color_palette("viridis", as_cmap=True)
sns.scatterplot(x="humidity", y="rainfall", data=df, palette="viridis")
plt.show()

# Line plot
#sns.color_palette("viridis", as_cmap=True)
#sns.lineplot(data=df[(df['humidity'] < 65)], x="N", y="rainfall", hue="label", palette="viridis")
#plt.show()

# Line plot
#  sns.color_palette("viridis", as_cmap=True)
# sns.lineplot(data=df[(df['humidity'] < 65)], x="P", y="rainfall", hue="label", palette="viridis")
# plt.show()


# Jointplot
sns.color_palette("viridis", as_cmap=True)
sns.jointplot(x="rainfall", y="humidity", data=df[(df['temperature'] < 30) & (df['rainfall'] > 120)], hue="label", palette="viridis")
plt.show()

# Subplots
# plt.subplot(1, 2, 1)
# sns.distplot(df['temperature'], color="purple", bins=15, hist_kws={'alpha': 0.2})
# plt.subplot(1, 2, 2)
# sns.distplot(df['ph'], color="green", bins=15, hist_kws={'alpha': 0.2})
# plt.show()

# ScatterMatrix graph
# from pandas.plotting import scatter_matrix
# scatter_matrix(df.drop('label',axis='columns'),figsize=(16,16),marker='.',alpha=0.4,c='green')
# plt.show()

# merging and ploting data from the new database
# Display the first and last few rows of the dataframe
print(df1.head())
print(df1.tail())

# Descriptive statistics for the new dataframe
print(df1.describe())

# Information about the new dataframe
print(df1.info())

# Correlation matrix for the new dataframe
# table that shows the correlation coefficients between many variables.
# Each cell in the table represents the correlation between two variables.
# The correlation coefficient is a statistical measure that describes the extent to which two variables change together
print(df1.corr())

# Columns in the new dataframe
print(df1.columns)

# Selecting specific columns in the new dataframe
print(df1[['N_SOIL', 'P_SOIL', 'TEMPERATURE', 'HUMIDITY', 'ph', 'RAINFALL', 'CROP_PRICE', 'CROP']])

# Selecting and renaming columns in the new dataframe
df1 = df1[['N_SOIL', 'P_SOIL', 'TEMPERATURE', 'HUMIDITY', 'ph', 'RAINFALL', 'CROP_PRICE', 'CROP']]

# Merges (df1 and df) based on the common 'CROP' column using an inner join, creating a new dataframe merged_df
# Merging dataframes on the 'CROP' column
merged_df = pd.merge(df1, df, on='CROP', how='inner')

# Improved drop operation for clarity
merged_df = merged_df.drop(columns='STATE')  # Add parentheses

# Display the merged dataframe
print(merged_df)

# Information about the merged dataframe
print(merged_df.info())  # Add parentheses to the function call

# Checking for null values in the merged dataframe
print(merged_df.isnull().sum())

# Scaling numerical columns using MinMaxScaler
numeric_df = merged_df.select_dtypes(include=['float64', 'int64'])
# It uses the `select_dtypes` method from pandas, which allows you to filter data based on data types.
# Here, we specify `include=['float64', 'int64']`
# to only select columns with data types of either 64-bit float or 64-bit integer.
scaler = MinMaxScaler()
normalized_df = pd.DataFrame(scaler.fit_transform(numeric_df), columns=numeric_df.columns)
# This line calculates the correlation matrix for the normalized data (`normalized_df`).
# The correlation matrix measures the linear relationship between pairs of features

# Correlation matrix for the normalized dataframe
correlation_matrix_normalized = normalized_df.corr()
cubehelix_palette = sns.cubehelix_palette(start=2, rot=0, dark=0, light=.95, reverse=True, as_cmap=True)

# Plotting a heatmap for the correlation matrix
plt.figure(figsize=(12, 10))
sns.heatmap(correlation_matrix_normalized, annot=True, cmap=cubehelix_palette, linewidths=.5)
plt.show()






