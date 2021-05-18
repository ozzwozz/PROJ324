

def main():
    DataFile = open("target_data.csv", "r")

    for x in DataFile:
        # where line[0] is actual location and line[1] is predicted
        Line = x.split("#")
        Actual_Loc = Line[0].split(",") # [0] is x, [1] is y
        Predictied_Loc = Line[1].split(",")# [0] is x, [1] is y

        x_accuracy = (Actual_Loc[0]/Predicted_Loc[0]) * 100
        y_accuracy = (Actual_Loc[1]/Predicted_Loc[1]) * 100


        print("Location",x,"x_accuracy",x_accuracy,"y_accuracy", y_accuracy)
        DataFile.close()



# calls main function, standard practice
if __name__ == "__main__":
    main()
