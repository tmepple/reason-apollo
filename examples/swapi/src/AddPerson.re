let ste = ReasonReact.string;

module AddPerson = [%graphql
  {|
    mutation addPerson($age: Int!, $name: String!) {
        createPerson(age: $age, name: $name) {
          name
        }
      }
|}
];

let component = ReasonReact.statelessComponent("AddPerson");

module AddPersonMutation = ReasonApollo.CreateMutation(AddPerson);

let make = _children => {
  ...component,
  render: _self => {
    let addPersonMutation = AddPerson.make(~name="Charley", ~age=42, ());
    <AddPersonMutation>
      ...(
           (mutation, {result}) => {
             Js.log(result);
             <div>
               <div>
                 (
                   switch (result) {
                   | Called => "Called" |> ste
                   | Loading => "Loading" |> ste
                   | Error(err) => "Error" |> ste
                   | NoData => "NoData" |> ste
                   | Data(data) =>
                     Js.log2("data", data);
                     "Data" |> ste;
                   | NotCalled => "NotCalled" |> ste
                   }
                 )
               </div>
               <button
                 onClick=(
                   (_) => {
                     mutation(
                       ~variables=addPersonMutation##variables,
                       ~refetchQueries=[|"getAllPersons"|],
                       (),
                     )
                     |> ignore;
                     Js.log("SEND");
                   }
                 )>
                 ("Add a person" |> ReasonReact.string)
               </button>
             </div>;
           }
         )
    </AddPersonMutation>;
  },
};
