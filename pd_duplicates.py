__author__ = "Vinay Kumar"
__copyright__ = "copyright 2018, Project flash217"
__maintainer__ = "Vinay Kumar"
__status__ = "Research & Development"


import pandas as pd

# Creating data
raw_data = {'first_name': ['Vinay','Prithvi','Vikas','Pooja','Arjun','Lakshmi'],
            'last_name': ['Kumar','Chauhan','Kumar','Prajapati','Prajapati','Prajapati'],
            'age': [27,3000,24,22,60,52],
            }
data_frame = pd.DataFrame(raw_data, columns=['first_name','last_name','age'])
print(f'data_frame:\n----------------\n{data_frame}\n')

# Identifying duplicates
print(f'data_frame.duplicated():\n----------------\n{data_frame.duplicated()}\n')

# Drop duplicates
print(f'data_frame.drop_duplicates():\n----------------\n{data_frame.drop_duplicates()}\n')

# Drop duplicates in the first/last name column but keep the last obs in the duplicated set
print(f'data_frame.drop_duplicates(["first_name"],keep="last"):\
        \n----------------\n{data_frame.drop_duplicates(["first_name"],keep="last")}\n')

print(f'data_frame.drop_duplicates(["last_name"],keep="last"):\
        \n----------------\n{data_frame.drop_duplicates(["last_name"],keep="last")}\n')

print(f'data_frame.drop_duplicates(["last_name"],keep="last"):\
        \n----------------\n{data_frame.drop_duplicates(["last_name"],keep="first")}\n')
